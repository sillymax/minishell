/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:13 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static char	*extract_value(char *subtoken)
{
	int	valid_key_name_len;

	valid_key_name_len = count_valid_key_name(subtoken);
	if (valid_key_name_len > 0 && is_equal(subtoken[valid_key_name_len]))
		subtoken += valid_key_name_len + 1;
	return (ft_strdup(subtoken));
}

static char	*get_directory_from_env(char *user)
{
	char	*home_directory;

	user = extract_until_delim(user, " /\\");
	if (*user == '\0')
	{
		free(user);
		home_directory = getenv("HOME");
		return (ft_strdup(home_directory));
	}
	free(user);
	return (NULL);
}

static char	*get_directory_from_passwd(char *user)
{
	char	*user_directory;

	user = extract_until_delim(user, " /\\");
	user_directory = find_user_directory(user);
	free(user);
	return (user_directory);
}

static char	*get_directory_from_users(char *user)
{
	char			*home_directory;
	DIR				*users_directory;
	struct dirent	*entry;

	user = extract_until_delim(user, " /\\");
	home_directory = NULL;
	users_directory = open_users_directory();
	if (!users_directory)
	{
		free(user);
		return (NULL);
	}
	entry = readdir(users_directory);
	while (entry)
	{
		home_directory = find_home_directory(entry->d_name, user);
		if (home_directory != NULL)
			break ;
		entry = readdir(users_directory);
	}
	closedir(users_directory);
	free(user);
	return (home_directory);
}

char	*expand_tilde(char *subtoken)
{
	char	*expanded_tilde;
	char	*result;
	char	*value;

	expanded_tilde = NULL;
	value = extract_value(subtoken);
	if (is_tilde(*value))
	{
		if (expanded_tilde == NULL)
			expanded_tilde = get_directory_from_env(value + 1);
		if (expanded_tilde == NULL)
			expanded_tilde = get_directory_from_passwd(value + 1);
		if (expanded_tilde == NULL)
			expanded_tilde = get_directory_from_users(value + 1);
		free(value);
		value = join_expanded_tilde_with_remains(expanded_tilde, subtoken);
		result = join_key_with_value(value, subtoken);
		free(value);
		free(subtoken);
		return (result);
	}
	free(value);
	return (subtoken);
}
