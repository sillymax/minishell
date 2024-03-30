/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:51:00 by ychng             #+#    #+#             */
/*   Updated: 2024/03/31 05:08:27 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
