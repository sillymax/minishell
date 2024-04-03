/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:46:53 by ychng             #+#    #+#             */
/*   Updated: 2024/04/03 11:45:18 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
