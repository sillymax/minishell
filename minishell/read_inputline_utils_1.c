/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:39:11 by ychng             #+#    #+#             */
/*   Updated: 2024/03/29 16:27:59 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	has_logicaloperr(char *token, int *openlogicalops)
{
	if (is_logicalop(token) == true)
	{
		(*openlogicalops)++;
		if (*openlogicalops > 0)
		{
			printf(
				"syntax error near unexpected token `%c%c'\n", \
				token[0], token[1]);
			return (true);
		}
	}
	else if (ft_strspn(token, " ") != ft_strlen(token))
		(*openlogicalops)--;
	return (false);
}

bool	has_bracketerr(char *token, int *openbrackets)
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
		{
			printf("syntax error near unexpected token `%c'\n", *token);
			return (true);
		}
		token++;
	}
	return (false);
}

bool	has_redirerr(char *token, int *openredir)
{
	while (*token && !is_logicalop(token))
	{
		if (is_redirection_n(token) && (*openredir == 0))
		{
			token += redirlen(token);
			(*openredir)++;
			continue ;
		}
		else if (!is_space(*token) && (*openredir > 0))
		{
			if (is_notvalidname(token))
				return (true);
			else
				(*openredir)--;
		}
		token++;
	}
	if (is_logicalop(token) && (*openredir > 0))
	{
		printf("syntax error near unexpected token `%s'\n", token);
		return (true);
	}
	return (false);
}

bool	has_noerror(char *input)
{
	int		openlogicalops;
	int		openbrackets;
	int		openredirs;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	openredirs = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops) \
			|| has_bracketerr(token, &openbrackets) \
			|| has_redirerr(token, &openredirs))
			return (free(token), false);
		free(token);
		token = get_next_token(NULL, false);
	}
	if (openredirs > 0)
	{
		printf("syntax error near unexpected `newline'\n");
		return (false);
	}
	return (true);
}
