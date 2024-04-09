/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:37:36 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

DIR	*open_users_directory(void)
{
	DIR	*users_directory;

	users_directory = opendir("/Users/");
	if (!users_directory)
		return (NULL);
	return (users_directory);
}

static bool	is_valid_entry(char *entry)
{
	return (ft_strcmp(entry, ".") != 0
		&& (ft_strcmp(entry, "..") != 0)
		&& (ft_strcmp(entry, "Shared") != 0)
		&& (*entry != '.'));
}

static bool	is_matching_user(char *entry, char *user)
{
	return (ft_strcmp(entry, user) == 0);
}

char	*find_home_directory(char *entry_name, char *user)
{
	if (is_valid_entry(entry_name) && is_matching_user(entry_name, user))
		return (ft_strjoin("/Users/", entry_name, ""));
	return (NULL);
}

char	*extract_key(char *subtoken)
{
	char	*equal_ptr;
	int		key_len;

	key_len = 0;
	equal_ptr = ft_strchr(subtoken, '=');
	if (equal_ptr)
	{
		key_len = equal_ptr - subtoken;
		if (is_equal(subtoken[key_len]))
			key_len++;
	}
	return (ft_strndup(subtoken, key_len));
}
