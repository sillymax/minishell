/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:33:26 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	contains_newline(char *remaining_line)
{
	return (ft_strchr(remaining_line, '\n'));
}

int	read_and_check(int fd, char *buffer, int buffer_size)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, buffer_size);
	if (bytes_read == -1)
	{
		printf("read failed for bytes_read\n");
		exit(-1);
	}
	return (bytes_read);
}
