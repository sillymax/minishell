/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:19:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 01:36:27 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	read_content(t_subtokenlist *currcmd, int tmpfd)
{
	char	*name;
	char	*readline;

	name = ft_strjoin(currcmd->head->subtoken, "\n", "");
	write(STDIN_FILENO, "docs> ", 7);
	readline = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (!ft_strncmp(readline, name, ft_strlen(readline)))
			break ;
		write(tmpfd, readline, ft_strlen(readline));
		free(readline);
		write(STDIN_FILENO, "docs> ", 7);
		readline = get_next_line(STDIN_FILENO);
	}
	free(name);
	free(readline);
}

char	*create_tmpfile(t_subtokenlist *currcmd)
{
	static int	count;
	char		*numb;
	char		*name;
	int			tmpfd;

	numb = ft_itoa(count);
	name = ft_strjoin("heredocs/temp_", ".txt", numb);
	count++;
	free(numb);
	tmpfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmpfd == -1)
	{
		printf("open failed for tmpfd\n");
		free(name);
		exit(-1);
	}
	read_content(currcmd, tmpfd);
	close(tmpfd);
	return (name);
}
