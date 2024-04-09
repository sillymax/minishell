/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:51:00 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

void	handle_pipecmd(char ***envp, int pipefd[], int prev_pipefd[], \
					t_subtokenlist **currcmd)
{
	int				infilefd;
	int				outfilefd;
	int				origstdin;
	int				origstdout;

	if (get_redirfd(envp, &infilefd, &outfilefd, currcmd) == -1)
		return ;
	origstdin = dup(STDIN_FILENO);
	origstdout = dup(STDOUT_FILENO);
	if (create_fork() == 0)
	{
		manage_piperedir_child(pipefd, prev_pipefd, infilefd, outfilefd);
		exit(run_cmd(envp, *currcmd));
	}
	else
		manage_piperedir_parent(pipefd, prev_pipefd);
	if (infilefd != 0)
		close(infilefd);
	if (outfilefd != 0)
		close(outfilefd);
	restore_originalfd(origstdin, origstdout);
}

void	handle_lastcmd(char ***envp, int prev_pipefd[], \
					t_subtokenlist **currcmd)
{
	int				infilefd;
	int				outfilefd;
	int				origio[2];
	int				exitcode;

	if (get_redirfd(envp, &infilefd, &outfilefd, currcmd) == -1)
		return ;
	init_origio(origio);
	manage_lastcmdredir(infilefd, outfilefd);
	if (prev_pipefd[0] == 0 && is_builtins(*currcmd))
	{
		exitcode = run_cmd(envp, *currcmd);
		update_exit_status(*envp, exitcode);
	}
	else
	{
		if (create_fork() == 0)
		{
			handle_lastcmd_child(prev_pipefd, infilefd);
			exit(run_cmd(envp, *currcmd));
		}
		else
			handle_lastcmd_parent(prev_pipefd);
	}
	restore_originalfd(origio[0], origio[1]);
}
