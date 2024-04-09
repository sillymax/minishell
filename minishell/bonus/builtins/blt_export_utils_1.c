/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:40:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	count_valid_args(char **envp, t_subtokennode *args)
{
	int				valid_args_count;
	t_subtokennode	*current_arg;

	valid_args_count = 0;
	current_arg = args;
	while (current_arg)
	{
		if (entry_has_valid_name(current_arg->subtoken))
		{
			if (is_not_duplicate(envp, current_arg->subtoken))
				valid_args_count++;
		}
		current_arg = current_arg->next;
	}
	return (valid_args_count);
}

void	add_valid_args(char **envp, t_subtokennode *args)
{
	int				envp_count;
	t_subtokennode	*current_arg;

	envp_count = count_2d_array_items(envp);
	current_arg = args;
	while (current_arg)
	{
		if (entry_has_valid_name(current_arg->subtoken))
		{
			if (is_not_duplicate(envp, current_arg->subtoken))
				envp[envp_count++] = ft_strdup(current_arg->subtoken);
			else
				handle_duplicate(envp, current_arg->subtoken);
		}
		current_arg = current_arg->next;
	}
	envp[envp_count] = NULL;
}

void	pad_envp_entry(char **envp)
{
	int	max_env_name_len;

	max_env_name_len = get_max_env_name_len(envp);
	while (*envp)
	{
		*envp = pad_env_name(*envp, max_env_name_len);
		envp++;
	}
}

void	trim_entry_pad(char **envp)
{
	while (*envp)
	{
		*envp = trim_env_name_pad(*envp);
		envp++;
	}
}

void	print_export_envp(char **envp)
{
	char	*name;
	char	*value;

	while (*envp)
	{
		if ((is_underscore(**envp) && is_equal(*(*envp + 1)))
			|| is_special_env_name(**envp))
		{
			envp++;
			continue ;
		}
		name = ft_strndup(*envp, ft_strcspn(*envp, "="));
		value = ft_strchr(*envp, '=');
		if (value)
		{
			value++;
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		else if (name && *name)
			printf("declare -x %s\n", name);
		free(name);
		envp++;
	}
}
