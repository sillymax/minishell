/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:50:22 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:17:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_val(bool *escaped, bool *inquote, char *quote_type)
{
	*escaped = false;
	*inquote = false;
	*quote_type = '\0';
}

bool	handle_redirection(char **token, int *openredir)
{
	if ((*openredir == 0) && is_redirection_n(*token))
	{
		*token += redirlen(*token);
		(*openredir)++;
		return (true);
	}
	return (false);
}

bool	handle_notvalidname(char *token, int *openredir)
{
	if ((*openredir > 0) && !is_space(*token))
	{
		if (is_notvalidname(token))
			return (true);
		(*openredir)--;
	}
	return (false);
}

bool	check_syntaxerror(char *token, int *openredir)
{
	if ((*openredir > 0) && is_logicalop(token))
	{
		printf("syntax error near unexpected token `%s'\n", token);
		return (true);
	}
	return (false);
}
