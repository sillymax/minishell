/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:36:42 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 18:20:42 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_quotes(char *subtoken, int subtokenlen)
{
	bool	escaped;
	bool	in_singquote;
	bool	in_doubquote;
	char	*result;
	char	*start;

	escaped = false;
	in_singquote = false;
	in_doubquote = false;
	result = malloc(ft_strlen(subtoken) + 1);
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	start = result;
	while (*subtoken)
	{
		if (!escaped && !in_singquote && is_backslash(*subtoken))
		{
			*result++ = *subtoken;
			escaped = true;
		}
		else if (!escaped && !in_doubquote && is_singquote(*subtoken))
			in_singquote = !in_singquote;
		else if (!escaped && !in_singquote && is_doubquote(*subtoken))
			in_doubquote = !in_doubquote;
		else
		{
			*result++ = *subtoken;
			escaped = false;
		}
		subtoken++;
	}
	*result = '\0';
	return (free(subtoken - subtokenlen), start);
}
