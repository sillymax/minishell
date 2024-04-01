/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:45:57 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 00:46:33 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
