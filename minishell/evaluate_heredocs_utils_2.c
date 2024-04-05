/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:19:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/06 04:15:44 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	read_content(t_subtokenlist *currcmd, int tmpfd)
{
	char	*name;
	char	*input;

	name = ft_strjoin(currcmd->head->subtoken, "\n", "");
	input = readline("docs> ");
	while (1)
	{
		if (!ft_strncmp(input, name, ft_strlen(input)))
			break ;
		write(tmpfd, input, ft_strlen(input));
		write(tmpfd, "\n", 1);
		free(input);
		input = readline("docs> ");
	}
	free(name);
	free(input);
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
