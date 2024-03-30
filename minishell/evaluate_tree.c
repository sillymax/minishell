/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:35:54 by ychng             #+#    #+#             */
/*   Updated: 2024/03/31 04:21:58 by ychng            ###   ########.fr       */
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

t_subtokenlist	*extract_redirection(t_subtokenlist **currcmd)
{
	t_subtokenlist	*cmdlist;
	t_subtokenlist	*redirlist;

	cmdlist = create_subtokenlist();
	redirlist = create_subtokenlist();
	while ((*currcmd)->head)
	{
		if (is_redirection((*currcmd)->head->subtoken))
		{
			link_subtokenlist(pop_subtokenlist_head(*currcmd), redirlist);
			link_subtokenlist(pop_subtokenlist_head(*currcmd), redirlist);
		}
		else
		{
			link_subtokenlist(pop_subtokenlist_head(*currcmd), cmdlist);
		}
	}
	*currcmd = cmdlist;
	return (redirlist);
}

void	manage_redirection(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;

	current = redirlist->head;
	while (current)
	{
		if (is_heredoc(current->subtoken))
		{
			int	tmp_fd;
		
			tmp_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (tmp_fd == -1)
			{
				printf("open failed for tmp_fd\n");
				exit(-1);
			}
			char	*name;
			char	*nextline;
		
			name = ft_strjoin(current->next->subtoken, "\n", "");
			nextline = get_next_line(STDIN_FILENO);
			while (1)
			{
				if (!ft_strncmp(name, nextline, ft_strlen(nextline)))
				{
					free(nextline);
					break ;
				}
				write(tmp_fd, nextline, ft_strlen(nextline));
				free(nextline);
				nextline = get_next_line(STDIN_FILENO);
			}
			free(name);
			// dup2(tmp_fd, STDIN_FILENO);
			// close(tmp_fd);
		}
		current = current->next;		
	}	
}

void	handle_pipecmd(char ***envp, int pipefd[], int prev_pipefd[], \
					t_subtokenlist *currcmd)
{
	t_subtokenlist	*redirlist;
	int				outfilefd;
	int				origstdout;

	redirlist = extract_redirection(&currcmd);
	outfilefd = get_outfilefd(redirlist);
	origstdout = dup(STDOUT_FILENO);
	if (create_fork() == 0)
	{
		if (prev_pipefd[0] != 0)
		{
			close(prev_pipefd[1]);
			dup2(prev_pipefd[0], STDIN_FILENO);
			close(prev_pipefd[0]);
		}
		if (outfilefd != 0)
		{
			dup2(outfilefd, STDOUT_FILENO);
			close(outfilefd);
		}
		else
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		manage_redirection(extract_redirection(&currcmd));
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
	close(outfilefd);
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);
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

bool	is_builtins(t_subtokenlist *currcmd)
{
	char	*cmd;

	cmd = currcmd->head->subtoken;
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	if (!ft_strcmp(cmd, "pwd"))
		return (true);
	if (!ft_strcmp(cmd, "export"))
		return (true);
	if (!ft_strcmp(cmd, "unset"))
		return (true);
	if (!ft_strcmp(cmd, "env"))
		return (true);
	if (!ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

bool	is_append(char *str)
{
	return (ft_strcmp(str, ">>") == 0);
}

bool	is_output(char *str)
{
	return (ft_strcmp(str, ">") == 0);
}

int	get_outfilefd(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;
	int				lastfd;
	char			*name;

	lastfd = 0;
	current = redirlist->head;
	while (current)
	{
		if (is_append(current->subtoken))
		{
			name = current->next->subtoken;
			lastfd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (is_output(current->subtoken))
		{
			name = current->next->subtoken;
			lastfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (lastfd == -1)
		{
			printf("open failed for lastfd\n");
			exit(-1);
		}
		current = current->next;
	}
	return (lastfd);
}

void	handle_lastcmd(char ***envp, int prev_pipefd[], \
					t_subtokenlist *currcmd)
{
	t_subtokenlist	*redirlist;
	int				outfilefd;
	int				origstdout;

	redirlist = extract_redirection(&currcmd);
	outfilefd = get_outfilefd(redirlist);
	origstdout = dup(STDOUT_FILENO);
	if (outfilefd != 0)
	{
		dup2(outfilefd, STDOUT_FILENO);
		close(outfilefd);
	}
	if (is_builtins(currcmd))
	{
		manage_redirection(extract_redirection(&currcmd));
		update_exit_status(*envp, run_cmd(envp, currcmd));
	}
	else
	{
		if (create_fork() == 0)
		{
			if (prev_pipefd[0] != 0)
			{
				close(prev_pipefd[1]);
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
			}
			manage_redirection(extract_redirection(&currcmd));
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
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);
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

	ft_bzero(prev_pipefd, sizeof(int) * 2);
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
