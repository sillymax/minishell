/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:51:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	get_redirfd(char ***envp, int *infilefd, int *outfilefd, \
			t_subtokenlist **currcmd)
{
	t_subtokenlist	*redirlist;

	redirlist = extract_redirection(currcmd);
	*infilefd = get_infilefd(redirlist);
	if (*infilefd == -1)
	{
		update_exit_status(*envp, 1);
		free_subtokenlist(redirlist);
		return (-1);
	}
	*outfilefd = get_outfilefd(redirlist);
	if (*outfilefd == -1)
	{
		update_exit_status(*envp, 1);
		free_subtokenlist(redirlist);
		return (-1);
	}
	free_subtokenlist(redirlist);
	return (0);
}

void	init_origio(int origio[])
{
	origio[0] = dup(STDIN_FILENO);
	origio[1] = dup(STDOUT_FILENO);
}

void	restore_originalfd(int origstdin, int origstdout)
{
	dup2(origstdin, STDIN_FILENO);
	close(origstdin);
	dup2(origstdout, STDOUT_FILENO);
	close(origstdout);
}

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
