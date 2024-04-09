/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:36:36 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

// *result = '\0' is in case, if 's1' is NULL
// ft_strcpy() won't terminate the result string
// ft_strcat() will segfault or give undefined behaviour
// in the first while loop, because it will run with garbage value
char	*custom_strjoin(char *s1, char *s2)
{
	int		joined_len;
	char	*result;

	joined_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (joined_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(1);
	}
	*result = '\0';
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free(s1);
	return (result);
}
