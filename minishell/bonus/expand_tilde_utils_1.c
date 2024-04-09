/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:39:27 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	count_valid_key_name(char *subtoken)
{
	int	count;

	count = 0;
	if (!is_number(subtoken[count]))
	{
		while (is_valid_env_name(subtoken[count]))
			count++;
	}
	return (count);
}

char	*extract_until_delim(char *user, char *delim)
{
	int	user_len;

	user_len = ft_strcspn(user, delim);
	if (is_backslash(user[user_len]) && !is_newline(user[user_len + 1]))
		user_len++;
	return (ft_strndup(user, user_len));
}

static int	open_passwd_file(void)
{
	int	fd;

	fd = open("/etc/passwd", O_RDONLY);
	return (fd);
}

static char	*find_directory(char *line, char *user)
{
	char	*field;
	int		field_column;

	field = ft_strtok(line, ":");
	if (field && ft_strcmp(line, user) != 0)
		return (NULL);
	field_column = 5;
	while (field_column--)
		field = ft_strtok(NULL, ":");
	return (ft_strdup(field));
}

char	*find_user_directory(char *user)
{
	int		fd;
	char	*line;
	char	*user_directory;

	user_directory = NULL;
	fd = open_passwd_file();
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		user_directory = find_directory(line, user);
		if (user_directory != NULL)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (user_directory);
}
