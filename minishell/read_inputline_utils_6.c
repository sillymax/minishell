/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:20:16 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 21:15:49 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	validlen(char *token, int *openbrackets)
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

int	validlenredir(char *token)
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
		else if (!is_space(*token) && (openredirs > 0))
		{
			if (is_notvalidname(token))
				return (lastredir - start);
			else
				openredirs--;
		}
		token++;
	}
	if (openredirs > 0)
		return (lastredir - start);
	return (token - start);
}

char	*extract_heredoc(char *input, int joinedlen)
{
	char	*joinedtokens;
	char	*subtoken;
	char	*result;
	int		openheredoc;

	joinedtokens = ft_strndup(input, joinedlen);
	free(input);
	if (!joinedtokens)
	{
		printf("ft_strndup failed for joinedtokens\n");
		exit(-1);
	}
	result = NULL;
	openheredoc = 0;
	subtoken = get_next_subtoken(joinedtokens);
	while (subtoken)
	{
		if (openheredoc == 0 && is_heredoc(subtoken))
		{
			openheredoc++;
			result = custom_strjoin(result, subtoken);
		}
		else if (openheredoc > 0)
		{
			openheredoc--;
			result = custom_strjoin(result, subtoken);
		}
		free(subtoken);
		subtoken = get_next_subtoken(NULL);
	}
	free(joinedtokens);
	return (result);
}

// bool	empty_bracket(char *input)
// {
// 	char	*innermost_adr;
// 	int		i;

// 	innermost_adr = ft_rstrchr(input, ')');
// 	if (innermost_adr == NULL)
// 		return (false);
// 	i = innermost_adr - input;
// 	while (--i > 0)
// 	{
// 		if (is_leftbracket(input[i]) || !is_space(input[i]))
// 			break ;
// 	}
// 	if (is_leftbracket(input[i]))
// 	{
// 		printf("syntax error near unexpected token `)'\n");
// 		return (true);
// 	}
// 	return (false);
// }