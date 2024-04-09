/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:40:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

bool	entry_has_valid_name(char *args)
{
	if (is_special_env_name(*args))
		return (false);
	else
	{
		while (is_valid_env_name(*args))
			args++;
		if (is_equal(*args) || *args == '\0')
			return (true);
	}
	return (false);
}

bool	is_not_duplicate(char **envp, char *args)
{
	int	args_name_len;

	while (*envp)
	{
		args_name_len = ft_strcspn(args, "=");
		if (!ft_strncmp(*envp, args, args_name_len))
			return (false);
		envp++;
	}
	return (true);
}

void	handle_duplicate(char **envp, char *args)
{
	bool	has_equal;
	int		args_name_len;

	has_equal = (bool)ft_strchr(args, '=');
	if (has_equal)
	{
		while (*envp)
		{
			args_name_len = ft_strcspn(args, "=");
			if (!ft_strncmp(*envp, args, args_name_len))
			{
				free(*envp);
				*envp = ft_strdup(args);
				break ;
			}
			envp++;
		}
	}
}
