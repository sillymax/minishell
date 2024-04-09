/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:47:42 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static int	count_expanded_escaped_len(char *subtoken)
{
	int			len;
	bool		escaped;
	bool		inquote;
	char		quote_type;

	len = 0;
	escaped = false;
	inquote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && should_escape(quote_type, subtoken))
		{
			escaped = true;
			subtoken++;
			continue ;
		}
		else if (!escaped && is_quote(*subtoken))
			toggle_inquote(*subtoken, &inquote, &quote_type);
		else
			escaped = false;
		len++;
		subtoken++;
	}
	return (len);
}

static void	expand_escaped_chars(char *result, char *subtoken)
{
	bool		escaped;
	bool		inquote;
	char		quote_type;

	escaped = false;
	inquote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && should_escape(quote_type, subtoken))
		{
			escaped = true;
			subtoken++;
			continue ;
		}
		else if (!escaped && is_quote(*subtoken))
			toggle_inquote(*subtoken, &inquote, &quote_type);
		else
			escaped = false;
		*result++ = *subtoken++;
	}
	*result = '\0';
}

char	*expand_escaped(char *subtoken)
{
	char	*result;
	int		expanded_len;

	expanded_len = count_expanded_escaped_len(subtoken);
	result = malloc(sizeof(char) * (expanded_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	expand_escaped_chars(result, subtoken);
	free(subtoken);
	return (result);
}
