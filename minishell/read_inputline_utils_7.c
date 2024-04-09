/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:08:02 by ychng             #+#    #+#             */
/*   Updated: 2024/04/09 14:17:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// if (*joininput == '\0')
// {
// 	free(joininput);
// 	return (ft_strdup("\n"));
// }
char	*format_joininput(char *joininput)
{
	return (joininput);
}

char	*alloc_joinedtokens(char *input, int joinedlen)
{
	char	*joinedtokens;

	joinedtokens = ft_strndup(input, joinedlen);
	free(input);
	if (!joinedtokens)
	{
		printf("ft_strndup failed for joinedtokens\n");
		exit(-1);
	}
	return (joinedtokens);
}
