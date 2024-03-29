/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:50:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/29 15:52:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	redirlen(char *token)
{
	if (ft_strncmp(token, "<<<", 3) == 0)
		return (3);
	if (ft_strncmp(token, "<<", 2) == 0
		|| (ft_strncmp(token, ">>", 2) == 0))
		return (2);
	if (ft_strncmp(token, "<", 1) == 0
		|| (ft_strncmp(token, ">", 1) == 0)
		|| (ft_strncmp(token, "|", 1) == 0))
		return (1);
	return (0);
}

bool	is_notvalidname(char *token)
{
	char	*subtoken;

	if (is_redirection_n(token))
	{
		subtoken = get_next_subtoken(token);
		printf("syntax error near unexpected token `%s'\n", subtoken);
		free(subtoken);
		return (true);
	}
	return (false);
}
