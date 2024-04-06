/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_9.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:26:12 by ychng             #+#    #+#             */
/*   Updated: 2024/04/06 16:31:22 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	has_alpha(char *str)
{
	while (*str)
	{
		if ((*str >= 'a' && *str <= 'z') \
			|| (*str >= 'A' && *str <= 'Z'))
			return (true);
		str++;
	}
	return (false);
}

bool	is_invalid_filename(char *bin)
{
	return (*bin == '\0' || !ft_strcmp(bin, ".") || !ft_strcmp(bin, "..") \
		|| !ft_strcmp(bin, "/") || !has_alpha(bin));
}

// if its a directory it will return false
// if its an executable it will return true
// if opendirdir can open, means it's directory
bool	is_executable(char *full_path)
{
	DIR	*dp;

	dp = opendir(full_path);
	if (dp != NULL)
	{
		closedir(dp);
		return (false);
	}
	return (true);
}
