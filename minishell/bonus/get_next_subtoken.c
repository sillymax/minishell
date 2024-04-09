/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_subtoken.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:44:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static int	skip_leading_spaces(char *remaining_token)
{
	return (ft_strspn(remaining_token, " "));
}

// The if is_redirection_n, is for strs that has multiple subtokens
// like "hi there|", see how the 'there' has '|' sticking together?
// so what the len_of_redirection will do is return the len of '|'
// which will increment the address of subtoken from '|' with 1
// which will point to \0
static char	*move_to_subtoken_end(char *subtoken)
{
	bool	escaped;
	bool	inquote;
	char	quote_type;

	if (is_redirection_n(subtoken))
		return (subtoken + len_of_redirection(subtoken));
	escaped = false;
	inquote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && !inquote && is_backslash(*subtoken))
			escaped = true;
		else if (!escaped && is_quote(*subtoken))
			toggle_inquote(*subtoken, &inquote, &quote_type);
		else if (!escaped && !inquote && is_space_or_redirection(subtoken))
			break ;
		else
			escaped = false;
		subtoken++;
	}
	return (subtoken);
}

static char	*duplicate_subtoken(char *subtoken, char *remaining_token)
{
	int	len;

	len = remaining_token - subtoken;
	if (len == 0)
		return (NULL);
	return (ft_strndup(subtoken, len));
}

char	*get_next_subtoken(char *token)
{
	static char	*remaining_token;
	char		*subtoken;

	if (token != NULL)
		remaining_token = token;
	if (!remaining_token || *remaining_token == '\0')
		return (NULL);
	subtoken = remaining_token;
	subtoken += skip_leading_spaces(remaining_token);
	remaining_token = move_to_subtoken_end(subtoken);
	return (duplicate_subtoken(subtoken, remaining_token));
}
