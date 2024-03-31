/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:51:00 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 06:46:33 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_infilefd(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;
	char			*name;
	int				infilefd;

	infilefd = 0;
	current = redirlist->head;
	while (current)
	{
		if (is_heredoc(current->subtoken))
		{
			name = current->next->subtoken;
			infilefd = open(name, O_RDONLY, 0644);
			if (infilefd == -1)
			{
				printf("open failed for infilefd\n");
				exit(-1);
			}
		}
		current = current->next;
	}
	return (infilefd);
}

void	handle_pipecmd(char ***envp, int pipefd[], int prev_pipefd[], \
					t_subtokenlist **currcmd)
{
	t_subtokenlist	*redirlist;
	int				infilefd;
	int				outfilefd;
	int				origstdin;
	int				origstdout;

	redirlist = extract_redirection(currcmd);
	infilefd = get_infilefd(redirlist);
	outfilefd = get_outfilefd(redirlist);
	free_subtokenlist(redirlist);
	origstdin = dup(STDIN_FILENO);
	origstdout = dup(STDOUT_FILENO);
	if (create_fork() == 0)
	{
		if (prev_pipefd[0] != 0)
		{
			close(prev_pipefd[1]);
			dup2(prev_pipefd[0], STDIN_FILENO);
			close(prev_pipefd[0]);
		}
		if (infilefd != 0)
		{
			dup2(infilefd, STDIN_FILENO);
			close(infilefd);
		}
		close(pipefd[0]);
		if (outfilefd != 0)
		{
			dup2(outfilefd, STDOUT_FILENO);
			close(outfilefd);
		}
		else
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(run_cmd(envp, *currcmd));
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
	if (infilefd != 0)
		close(infilefd);
	if (outfilefd != 0)
		close(outfilefd);
	dup2(origstdin, STDIN_FILENO);
	close(origstdin);
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);
}

void	handle_lastcmd(char ***envp, int prev_pipefd[], \
					t_subtokenlist **currcmd)
{
	t_subtokenlist	*redirlist;
	int				infilefd;
	int				outfilefd;
	int				origstdin;
	int				origstdout;

	redirlist = extract_redirection(currcmd);
	infilefd = get_infilefd(redirlist);
	outfilefd = get_outfilefd(redirlist);
	free_subtokenlist(redirlist);
	origstdin = dup(STDIN_FILENO);
	origstdout = dup(STDOUT_FILENO);
	if (infilefd != 0)
	{
		dup2(infilefd, STDIN_FILENO);
		close(infilefd);
	}
	if (outfilefd != 0)
	{
		dup2(outfilefd, STDOUT_FILENO);
		close(outfilefd);
	}
	if (prev_pipefd[0] == 0)
		update_exit_status(*envp, run_cmd(envp, *currcmd));
	else
	{
		if (create_fork() == 0)
		{
			if (prev_pipefd[0] != 0)
			{
				close(prev_pipefd[1]);
				if (infilefd == 0)
					dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
			}
			exit(run_cmd(envp, *currcmd));
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
	dup2(origstdin, STDIN_FILENO);
	close(origstdin);
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);
}
