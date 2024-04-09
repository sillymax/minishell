/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:19:32 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	handle_no_args(char **envp)
{
	handle_oldpwd(envp);
	move_to_home_directory();
	handle_pwd(envp);
	return (0);
}

static void	handle_dot(char **envp)
{
	handle_oldpwd(envp);
}

static void	handle_dotdot(char **envp)
{
	handle_oldpwd(envp);
	move_to_parent_directory();
	handle_pwd(envp);
}

static void	handle_path(char **envp, char *path)
{
	char	*cwd;

	handle_oldpwd(envp);
	if (is_forwardslash(path[0]))
	{
		if (chdir(path) != 0)
			printf("chdir failed for %s\n", path);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			printf("getcwd failed for cwd\n");
			exit(-1);
		}
		path = ft_strjoin(cwd, path, "/");
		free(cwd);
		if (chdir(path) != 0)
			printf("chdir failed for %s\n", path);
		free(path);
	}
	handle_pwd(envp);
}

int	blt_cd(char **envp, t_subtokennode *args)
{
	if (args == NULL)
		return (handle_no_args(envp));
	if (args->next == NULL)
	{
		if (!ft_strcmp(args->subtoken, ".."))
			handle_dotdot(envp);
		else if (!ft_strcmp(args->subtoken, "."))
			handle_dot(envp);
		else
			handle_path(envp, args->subtoken);
	}
	else
	{
		printf("too many arguments\n");
		return (1);
	}
	return (0);
}
