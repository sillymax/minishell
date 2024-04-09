/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 02:55:05 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

char	*join_expanded_tilde_with_remains(char *directory, \
			char *remains)
{
	char	*result;
	int		joined_len;

	if (directory)
		remains += ft_strcspn(remains, " /\\");
	joined_len = ft_strlen(directory) + ft_strlen(remains);
	result = malloc(sizeof(char) * (joined_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	*result = '\0';
	ft_strcpy(result, directory);
	ft_strcat(result, remains);
	free(directory);
	return (result);
}

// My extract key will extratc if there is '=' sign in subtoken
// But cases where value is the exact same as subtoken like
// (value && subtoken) = m=~asdas then i will print m=m=~asdas
// So to fix that I added the if condition, to compare
// the first key name including the equal if its the same
// then I don't want to print key
char	*join_key_with_value(char *value, char *subtoken)
{
	char	*key;

	key = extract_key(subtoken);
	if (ft_strncmp(key, value, ft_strlen(key)) == 0)
	{
		free(key);
		key = NULL;
	}
	return (custom_strjoin(key, value));
}
