/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:01:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static char	*read_fd_until_newline(int fd, char *remaining_line)
{
	int		buffer_size;
	char	*buffer;
	int		bytes_read;

	buffer_size = 4096;
	buffer = malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
	{
		printf("malloc failed for buffer\n");
		exit(-1);
	}
	bytes_read = 0;
	while (!contains_newline(remaining_line))
	{
		bytes_read = read_and_check(fd, buffer, buffer_size);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		remaining_line = custom_strjoin(remaining_line, buffer);
	}
	free(buffer);
	return (remaining_line);
}

static char	*extract_before_newline(char *remaining_line)
{
	char	*result;
	int		len;

	if (!remaining_line || (*remaining_line == '\0'))
		return (NULL);
	len = ft_strcspn(remaining_line, "\n");
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	ft_strncpy(result, remaining_line, len);
	if (remaining_line[len] == '\n')
		result[len++] = '\n';
	result[len] = '\0';
	return (result);
}

static char	*extract_after_newline(char *remaining_line)
{
	char	*newline_ptr;
	char	*result;

	if (!remaining_line)
		return (NULL);
	newline_ptr = ft_strchr(remaining_line, '\n');
	if (!newline_ptr)
	{
		free(remaining_line);
		return (NULL);
	}
	result = ft_strdup(newline_ptr + 1);
	if (!result)
	{
		printf("ft_strdup failed for result\n");
		exit(-1);
	}
	free(remaining_line);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*remaining_line;
	char		*line;

	if (fd < 0)
		return (NULL);
	remaining_line = read_fd_until_newline(fd, remaining_line);
	line = extract_before_newline(remaining_line);
	remaining_line = extract_after_newline(remaining_line);
	return (line);
}
