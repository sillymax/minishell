/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:39:19 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 17:45:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*find_token_end(char *remaining_input, bool withbracket)
{
	bool	escaped;
	bool	inquote;
	char	quote_type;

	if (is_bracket_or_logical_operator(remaining_input, withbracket))
		return (remaining_input + len_of_operator(remaining_input));
	escaped = false;
	inquote = false;
	quote_type = '\0';
	while (*remaining_input)
	{
		if (!escaped && !is_singquote(quote_type)
			&& is_backslash(*remaining_input))
			escaped = true;
		else if (!escaped && is_quote(*remaining_input))
			toggle_inquote(*remaining_input, &inquote, &quote_type);
		else if (!escaped && !inquote && \
				is_bracket_or_logical_operator(remaining_input, withbracket))
			break ;
		else
			escaped = false;
		remaining_input++;
	}
	return (remaining_input);
}

static char	*duplicate_token(char *token, char *remaining_input)
{
	int	len;

	len = ft_strlen(token) - ft_strlen(remaining_input);
	return (ft_strndup(token, len));
}

char	*get_next_token(char *input, bool withbracket)
{
	static char	*remaining_input;
	char		*token;

	if (input != NULL)
		remaining_input = input;
	if (!remaining_input || *remaining_input == '\0')
		return (NULL);
	token = remaining_input;
	remaining_input = find_token_end(remaining_input, withbracket);
	return (duplicate_token(token, remaining_input));
}
