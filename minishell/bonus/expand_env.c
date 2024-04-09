/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 06:18:41 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static int	count_expanded_len(char *subtoken, char **envp)
{
	int		len;
	char	*env;

	len = 0;
	env = get_next_env(subtoken);
	while (env)
	{
		len += count_len_until_env(subtoken, env);
		len += count_env_value_len(env, envp);
		subtoken += skip_env(env);
		free(env);
		env = get_next_env(NULL);
	}
	len += ft_strlen(subtoken);
	return (len);
}

static void	fill_result(char *result, char *subtoken, char **envp)
{
	char	*env;

	env = get_next_env(subtoken);
	while (env)
	{
		while (*subtoken && subtoken != ft_strstr(subtoken, env))
			*result++ = *subtoken++;
		*result = '\0';
		result = append_env_value(result, env, envp);
		subtoken += skip_env(env);
		free(env);
		env = get_next_env(NULL);
	}
	*result = '\0';
	ft_strcat(result, subtoken);
}

char	*expand_env(char *subtoken, char **envp)
{
	char	*result;
	int		expanded_len;

	expanded_len = count_expanded_len(subtoken, envp);
	result = malloc(sizeof(char) * (expanded_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	fill_result(result, subtoken, envp);
	free(subtoken);
	return (result);
}
