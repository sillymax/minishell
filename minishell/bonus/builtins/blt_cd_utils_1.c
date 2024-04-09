/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:21:59 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

void	handle_oldpwd(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "OLDPWD", 6) && is_equal((*envp)[6]))
		{
			free(*envp);
			*envp = update_oldpwd();
		}
		envp++;
	}
}

void	handle_pwd(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PWD", 3) && is_equal((*envp)[3]))
		{
			free(*envp);
			*envp = update_pwd();
		}
		envp++;
	}
}

void	move_to_home_directory(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
		printf("getenv failed for home_dir\n");
	if (chdir(home_dir) != 0)
		printf("chdir failed for %s\n", home_dir);
}

void	move_to_parent_directory(void)
{
	if (chdir("..") != 0)
		printf("chdir failed for ..\n");
}
