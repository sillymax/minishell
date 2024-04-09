/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:33:54 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static char	*unset_entry(char *entry, t_subtokennode *args)
{
	int				env_name_len;
	t_subtokennode	*current_arg;

	if (ft_strchr(args->subtoken, '=') != NULL)
		return (entry);
	env_name_len = ft_strcspn(entry, "=");
	current_arg = args;
	while (current_arg)
	{
		if (is_special_env_name(*entry))
			return (entry);
		if (!ft_strncmp(entry, args->subtoken, env_name_len))
		{
			entry = ft_realloc(entry, ft_strlen(entry) + 1, 1);
			if (!entry)
			{
				printf("ft_realloc failed for entry\n");
				exit(-1);
			}
			*entry = '\0';
			return (entry);
		}
		current_arg = current_arg->next;
	}
	return (entry);
}

int	blt_unset(char **envp, t_subtokennode *args)
{
	while (*envp)
	{
		*envp = unset_entry(*envp, args);
		envp++;
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**temp;

// 	temp = envp;
// 	envp = malloc(sizeof(char *) * (count_envp_size(envp) + 1));
// 	from_envp(envp, temp);

// 	t_subtokennode	first;
// 	t_subtokennode	second;
// 	t_subtokennode	third;
// 	t_subtokennode	fourth;
// 	t_subtokennode	fifth;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = &fourth;
// 	fourth.next = &fifth;;
// 	fifth.next = NULL;

// 	first.subtoken = "XDG_RUNTIME_DIR";
// 	second.subtoken = "bye";
// 	third.subtoken = "LOGNAME";
// 	fourth.subtoken = "COLORTERM=";
// 	fifth.subtoken = "NAME=MAX";

// 	blt_unset(envp, NULL, &first);
// 	int	i;

// 	i = -1;
// 	blt_export(&envp, NULL);
// 	free_envp(envp);
// }