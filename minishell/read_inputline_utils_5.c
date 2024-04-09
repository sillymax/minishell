/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:22:33 by ychng             #+#    #+#             */
/*   Updated: 2024/04/09 15:57:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	dup_stdoutfd(char *input)
{
	int	stdoutfd;

	stdoutfd = dup(STDOUT_FILENO);
	if (stdoutfd == -1)
	{
		printf("dup failed for stdoutfd\n");
		free(input);
		exit(-1);
	}
	return (stdoutfd);
}

int	dup_nullfd(char *input)
{
	int	nullfd;

	nullfd = open("/dev/null", O_WRONLY);
	if (nullfd == -1)
	{
		printf("open failed for nullfd\n");
		free(input);
		exit(-1);
	}
	return (nullfd);
}

char	*trim_errorpart(char *input)
{
	int		joinedlen;
	char	*token;

	joinedlen = 0;
	token = process_token(input, &joinedlen);
	return (extract_heredoc(input, joinedlen));
}
