/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:56:14 by ychng             #+#    #+#             */
/*   Updated: 2024/04/09 15:59:21 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// in opens is
// int	openlogicalops;
// int	openbrackets;
// int	openredirs;
char	*process_token(char *input, int *joinedlen)
{
	int		opens[3];
	char	*token;

	ft_bzero(opens, sizeof(int) * 3);
	token = get_next_token(input, false);
	while (token)
	{
		if (check_error_conditions(token, joinedlen, opens) > 0)
			break ;
		*joinedlen += ft_strlen(token);
		free(token);
		token = get_next_token(NULL, false);
	}
	return (token);
}

char	*extract_heredoc(char *input, int joinedlen)
{
	char	*joinedtokens;
	char	*subtoken;
	char	*result;
	int		openheredoc;

	joinedtokens = alloc_joinedtokens(input, joinedlen);
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
	return (free(joinedtokens), result);
}
