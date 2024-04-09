/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_8.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:20:16 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 00:53:38 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	validlen(char *token, int *openbrackets)
{
	char	*start;

	token += ft_strspn(token, " ");
	start = token;
	while (*token)
	{
		if (((start == token) || *openbrackets > 0) && is_leftbracket(*token))
			(*openbrackets)++;
		else if (((start != token) && *openbrackets > 0) \
				&& is_rightbracket(*token))
			(*openbrackets)--;
		else if (((start == token) && is_rightbracket(*token)) \
			|| ((start != token) && is_bracket(*token)))
			break ;
		token++;
	}
	return (token - start);
}

static int	validlenredir(char *token)
{
	char		*start;
	char		*lastredir;
	int			openredirs;

	openredirs = 0;
	start = token;
	while (*token)
	{
		if (is_redirection_n(token) && (openredirs == 0))
		{
			lastredir = token;
			openredirs++;
			token += redirlen(token);
			continue ;
		}
		else if (!is_space(*token) && (openredirs > 0) \
				&& is_notvalidname(token))
			return (lastredir - start);
		else if (!is_space(*token) && (openredirs > 0))
			openredirs--;
		token++;
	}
	if (openredirs > 0)
		return (lastredir - start);
	return (token - start);
}

int	check_error_conditions(char *token, int *joinedlen, int opens[])
{
	if (has_logicaloperr(token, &opens[0]))
	{
		free(token);
		return (1);
	}
	else if (has_bracketerr(token, &opens[1]))
	{
		*joinedlen += validlen(token, &opens[1]);
		free(token);
		return (1);
	}
	else if (has_redirerr(token, &opens[2]) || opens[2] > 0)
	{
		*joinedlen += validlenredir(token);
		free(token);
		return (1);
	}
	return (0);
}

char	*alloc_joinedtokens(char *input, int joinedlen)
{
	char	*joinedtokens;

	joinedtokens = ft_strndup(input, joinedlen);
	free(input);
	if (!joinedtokens)
	{
		printf("ft_strndup failed for joinedtokens\n");
		exit(-1);
	}
	return (joinedtokens);
}
