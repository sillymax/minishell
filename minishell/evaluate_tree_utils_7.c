/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:02:36 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 00:45:35 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	run_cmd(char ***envp, t_subtokenlist *currcmd)
{
	char			*cmd;
	t_subtokennode	*args;

	if (currcmd->head == NULL)
		return (0);
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
