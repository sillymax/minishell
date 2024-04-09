/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:18:21 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static char	*get_cwd(void)
{
	char	*cwd;
	int		size;

	cwd = NULL;
	size = 1024;
	while (size < 4096)
	{
		cwd = malloc(size);
		if (!cwd)
		{
			printf("malloc failed for cwd\n");
			exit(-1);
		}
		if (getcwd(cwd, size))
			break ;
		free(cwd);
		size *= 2;
	}
	if (cwd == NULL)
	{
		printf("getcwd failed\n");
		exit(-1);
	}
	return (cwd);
}

char	*update_oldpwd(void)
{
	char	*cwd;
	char	*new_entry;

	cwd = get_cwd();
	new_entry = ft_strjoin("OLDPWD=", cwd, "");
	if (!new_entry)
	{
		printf("ft_strjoin failed for new_entry\n");
		free(cwd);
		exit(-1);
	}
	free(cwd);
	return (new_entry);
}

char	*update_pwd(void)
{
	char	*cwd;
	char	*new_entry;

	cwd = get_cwd();
	new_entry = ft_strjoin("PWD=", cwd, "");
	if (!new_entry)
	{
		printf("ft_strjoin failed for new_entry\n");
		free(cwd);
		exit(-1);
	}
	free(cwd);
	return (new_entry);
}
