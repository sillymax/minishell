/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:02 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 17:45:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*find_env_start(char *remaining_subtoken)
{
	bool	escaped;
	bool	inquote;
	char	quote_type;

	escaped = false;
	inquote = false;
	quote_type = '\0';
	while (*remaining_subtoken)
	{
		if (!escaped && !is_singquote(quote_type)
			&& is_backslash(*remaining_subtoken))
			escaped = true;
		else if (!escaped && is_quote(*remaining_subtoken))
			toggle_inquote(*remaining_subtoken, &inquote, &quote_type);
		else if (!escaped && !is_singquote(quote_type)
			&& is_env_var(remaining_subtoken))
			break ;
		else
			escaped = false;
		remaining_subtoken++;
	}
	return (remaining_subtoken);
}

static char	*skip_env_name(char *remaining_subtoken)
{
	if (is_dollar_sign(*remaining_subtoken))
	{
		remaining_subtoken++;
		if (is_special_env_name(*remaining_subtoken))
		{
			remaining_subtoken++;
			return (remaining_subtoken);
		}
		while (*remaining_subtoken && is_valid_env_name(*remaining_subtoken))
			remaining_subtoken++;
	}
	return (remaining_subtoken);
}

static char	*duplicate_env_var(char *env, char *remaining_subtoken)
{
	int	len;

	len = remaining_subtoken - env;
	if (len == 0)
		return (NULL);
	return (ft_strndup(env, len));
}

char	*get_next_env(char *subtoken)
{
	static char	*remaining_subtoken;
	char		*env;

	if (subtoken != NULL)
		remaining_subtoken = subtoken;
	if (!remaining_subtoken || *remaining_subtoken == '\0')
		return (NULL);
	remaining_subtoken = find_env_start(remaining_subtoken);
	env = remaining_subtoken;
	remaining_subtoken = skip_env_name(remaining_subtoken);
	return (duplicate_env_var(env, remaining_subtoken));
}

// int	main(void)
// {
// 	char	*subtoken;
// 	char	*env;

// 	subtoken = readline("> ");
// 	env = get_next_env(subtoken);
// 	while (env)
// 	{
// 		printf("%s\n", env);
// 		env = get_next_env(NULL);
// 	}
// }