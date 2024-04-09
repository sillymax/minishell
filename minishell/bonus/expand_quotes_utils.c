/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:38:06 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

char	*alloc_result(char *subtoken)
{
	char	*result;

	result = malloc(ft_strlen(subtoken) + 1);
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	return (result);
}

void	handle_normchar(char **result, char **subtoken, bool *escaped, \
					bool should_escape)
{
	**result = **subtoken;
	(*result)++;
	*escaped = should_escape;
}
