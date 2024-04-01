/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:51:00 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 00:42:41 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_redirfd(char ***envp, int *infilefd, int *outfilefd, \
			t_subtokenlist *currcmd)
{
	t_subtokenlist	*redirlist;

	redirlist = extract_redirection(currcmd);
	infilefd = get_infilefd(redirlist);
	if (infilefd == -1)
	{
		update_exit_status(*envp, 1);
		free_subtokenlist(redirlist);
		return (-1);
	}
	outfilefd = get_outfilefd(redirlist);
	if (outfilefd == -1)
	{
		update_exit_status(*envp, 1);
		free_subtokenlist(redirlist);
		return (-1);
	}
	free_subtokenlist(redirlist);
	return (0);
}

void	manage_piperedir_child(int pipefd[], int prev_pipefd[], \
							int infilefd, int outfilefd)
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
}

void	manage_piperedir_parent(int pipefd[], int prev_pipefd[])
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
	prev_pipefd[0] = pipefd[0];
	prev_pipefd[1] = pipefd[1];
}

void	restore_originalfd(int origstdin, int origstdout)
{
	dup2(origstdin, STDIN_FILENO);
	close(origstdin);
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);	
}

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

void	manage_lastcmdredir(int infilefd, int outfilefd)
{
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
}

void	handle_lastcmd_child(int prev_pipefd[], int infilefd)
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[1]);
		if (infilefd == 0)
			dup2(prev_pipefd[0], STDIN_FILENO);
		close(prev_pipefd[0]);
	}	
}

void	handle_lastcmd_parent(int prev_pipefd[])
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
}

void	handle_lastcmd(char ***envp, int prev_pipefd[], \
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
	manage_lastcmdredir(infilefd, outfilefd);
	if (prev_pipefd[0] == 0 && is_builtins(*currcmd))
		update_exit_status(*envp, run_cmd(envp, *currcmd));
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
	restore_originalfd(origstdin, origstdout);
}
