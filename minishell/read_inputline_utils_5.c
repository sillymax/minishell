/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:22:33 by ychng             #+#    #+#             */
/*   Updated: 2024/03/29 16:12:33 by ychng            ###   ########.fr       */
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
	int		openlogicalops;
	int		openbrackets;
	int		openredirs;
	int		joinedlen;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	joinedlen = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops))
		{
			free(token);
			break ;
		}
		else if (has_bracketerr(token, &openbrackets))
		{
			joinedlen += validlen(token, &openbrackets);
			free(token);
			break ;
		}
		else if (has_redirerr(token, &openredirs) || openredirs > 0)
		{
			joinedlen += validlenredir(token);
			free(token);
			break ;
		}
		joinedlen += ft_strlen(token);
		free(token);
		token = get_next_token(NULL, false);
	}
	return (extract_heredoc(input, joinedlen));
}
