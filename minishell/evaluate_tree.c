/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:35:54 by ychng             #+#    #+#             */
/*   Updated: 2024/03/30 01:56:32 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("fork failed for pid\n");
		exit(-1);
	}
	return (pid);
}

char	**currcmd_to_2d_array(t_subtokenlist *currcmd)
{
	char			**result;
	t_subtokennode	*current;
	int				i;

	result = malloc(sizeof(char *) * (count_subtokenlist(currcmd) + 1));
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = 0;
	current = currcmd->head;
	while (current)
	{
		result[i] = ft_strdup(current->subtoken);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
		}
		i++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

char	*find_full_bin_path(char *bin, char **envp)
{
	int		i;
	char	*path;
	char	*full_path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ":");
		while (path)
		{
			full_path = ft_strjoin(path, bin, "/");
			if (access(full_path, F_OK) == 0)
				return (full_path);
			free(full_path);
			path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

int	run_execve(char **envp, t_subtokenlist *currcmd)
{
	char	**args;
	char	*bin;

	args = currcmd_to_2d_array(currcmd);
	bin = find_full_bin_path(args[0], envp);
	if (bin == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return (-1);
	}
	execve(bin, args, envp);
	free_double_array(args);
	return (-1);
}

int	run_cmd(char ***envp, t_subtokenlist *currcmd)
{
	char			*cmd;
	t_subtokennode	*args;

	cmd = currcmd->head->subtoken;
	args = currcmd->head->next;
	if (!ft_strcmp(cmd, "echo"))
		return (blt_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (blt_cd(*envp, args));
	if (!ft_strcmp(cmd, "pwd"))
		return (blt_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (blt_export(envp, args));
	if (!ft_strcmp(cmd, "unset"))
		return (blt_unset(*envp, args));
	if (!ft_strcmp(cmd, "env"))
		return (blt_env(*envp));
	if (!ft_strcmp(cmd, "exit"))
		return (blt_exit(args));
	return (run_execve(*envp, currcmd));
}

void	handle_pipecmd(char ***envp, int pipefd[], int prev_pipefd[], \
					t_subtokenlist *currcmd)
{
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
	{
		if (prev_pipefd[0] != 0)
		{
			close(prev_pipefd[1]);
			dup2(prev_pipefd[0], STDIN_FILENO);
			close(prev_pipefd[0]);
		}
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(run_cmd(envp, currcmd));
	}
	else
	{
		if (prev_pipefd[0] != 0)
		{
			close(prev_pipefd[0]);
			close(prev_pipefd[1]);
		}
		prev_pipefd[0] = pipefd[0];
		prev_pipefd[1] = pipefd[1];
	}
}

void	update_exit_status(char **envp, int exit_status)
{
	char	*envname;
	char	*exitcode;

	while (*envp)
	{
		if (is_question_mark(**envp) && is_equal(*(*envp + 1)))
		{
			envname = ft_strndup(*envp, ft_strcspn(*envp, "=") + 1);
			if (!envname)
			{
				printf("ft_strndup failed for envname\n");
				exit(-1);
			}
			exitcode = ft_itoa(exit_status);
			if (!exitcode)
			{
				printf("ft_itoa failed for exitcode\n");
				exit(-1);
			}
			free(*envp);
			*envp = custom_strjoin(envname, exitcode);
			free(exitcode);
		}
		envp++;
	}
}

void	handle_lastcmd(char ***envp, int prev_pipefd[], \
					t_subtokenlist *currcmd)
{
	pid_t	pid;

	if (prev_pipefd[0] == 0)
		update_exit_status(*envp, run_cmd(envp, currcmd));
	else
	{
		pid = create_fork();
		if (pid == 0)
		{
			if (prev_pipefd[0] != 0)
			{
				close(prev_pipefd[1]);
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
			}
			exit(run_cmd(envp, currcmd));
		}
		else
		{
			if (prev_pipefd[0] != 0)
			{
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
		}
	}
}

void	exec_cmd(char ***envp, int prev_pipefd[], \
			t_subtokenlist *currcmd, bool is_lastcmd)
{
	int	pipefd[2];

	if (!is_lastcmd)
	{
		if (pipe(pipefd) == -1)
		{
			printf("pipe failed for pipefd\n");
			exit(-1);
		}
		handle_pipecmd(envp, pipefd, prev_pipefd, currcmd);
	}
	else
		handle_lastcmd(envp, prev_pipefd, currcmd);
}

void	wait_for_forks(char **envp)
{
	int	exit_status;

	while (waitpid(-1, &exit_status, 0) > 0)
		update_exit_status(envp, WEXITSTATUS(exit_status));
}

int	get_exitstatus(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "?=", 2))
			break ;
		envp++;
	}
	return (ft_atoi(*envp + 2));
}

bool	evaluate_cmd(t_tokennode *token, char ***envp)
{
	int				prev_pipefd[2];
	t_subtokenlist	*subtokenlist;
	t_subtokenlist	*currcmd;

	subtokenlist = token->subtokenlist;
	while (subtokenlist->head)
	{
		currcmd = create_subtokenlist();
		while (subtokenlist->head && !is_pipe(*(subtokenlist->head->subtoken)))
			link_subtokenlist(pop_subtokenlist_head(subtokenlist), currcmd);
		exec_cmd(envp, prev_pipefd, currcmd, !subtokenlist->head);
		if (subtokenlist->head)
			free_subtokennode(pop_subtokenlist_head(subtokenlist));
		free_subtokenlist(currcmd);
	}
	wait_for_forks(*envp);
	return (get_exitstatus(*envp) == 0);
}

char	*getoperator(t_treenode *node)
{
	t_subtokenlist	*subtokenlist;
	t_subtokennode	*currsub;

	subtokenlist = node->token->subtokenlist;
	currsub = subtokenlist->head;
	return (currsub->subtoken);
}

bool	evaluate_tree(t_treenode *root, char ***envp)
{
	bool	left;

	if (root == NULL)
		return (false);
	left = evaluate_tree(root->left, envp);
	if (!ft_strcmp(getoperator(root), "&&"))
	{
		if (left == NULL)
			return (false);
		return (evaluate_tree(root->right, envp));
	}
	else if (!ft_strcmp(getoperator(root), "||"))
	{
		if (left == NULL)
			return (evaluate_tree(root->right, envp));
	}
	return (evaluate_cmd(root->token, envp));
}
