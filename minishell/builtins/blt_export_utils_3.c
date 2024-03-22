/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:44:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/23 01:15:20 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_max_env_name_len(char **envp)
{
	int	maxlen;
	int	len;

	maxlen = 0;
	while (*envp)
	{
		len = ft_strcspn(*envp, "=");
		if (maxlen < len)
			maxlen = len;
		envp++;
	}
	return (maxlen);
}

char	*pad_env_name(char *entry, int maxlen)
{
	int		env_name_len;
	char	*result;

	env_name_len = ft_strcspn(entry, "=");
	if (env_name_len < maxlen)
	{
		result = ft_strndup(entry, env_name_len);
		result = ft_realloc(result, env_name_len + 1, maxlen + 1);
		if (!result)
		{
			printf("ft_realloc failed for result\n");
			exit(-1);
		}
		ft_memset(&result[env_name_len], ' ', maxlen - env_name_len);
		result[maxlen] = '\0';
		result = custom_strjoin(result, ft_strchr(entry, '='));
		free(entry);
		return (result);
	}
	return (entry);
}

char	*trim_env_name_pad(char *entry)
{
	int		old_size;
	int		new_size;
	char	*result;

	old_size = ft_strcspn(entry, "=") + 1;
	new_size = ft_strcspn(entry, " ") + 1;
	result = ft_realloc(ft_strndup(entry, old_size), old_size, new_size);
	if (!result)
	{
		printf("ft_realloc failed for result\n");
		exit(-1);
	}
	result[new_size] = '\0';
	result = custom_strjoin(result, ft_strchr(entry, '='));
	free(entry);
	return (result);
}
