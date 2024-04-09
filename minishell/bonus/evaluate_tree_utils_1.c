/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:50:56 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

void	exec_cmd(char ***envp, int prev_pipefd[], \
			t_subtokenlist **currcmd, bool is_lastcmd)
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
