/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_envp_with_special.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:18:52 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static void	add_to_envp(char ***envp, char *new_entry)
{
	int		count;
	int		old_size;
	int		new_size;
	char	**new_envp;

	count = count_2d_array_items(*envp);
	old_size = sizeof(char *) * (count + 1);
	new_size = sizeof(char *) * (count + 2);
	new_envp = ft_realloc(*envp, old_size, new_size);
	if (!new_envp)
	{
		printf("ft_realloc failed for new_envp\n");
		exit(-1);
	}
	new_envp[count] = ft_strdup(new_entry);
	if (!new_envp[count])
	{
		printf("ft_strdup failed for new_envp[%d]\n", count);
		exit(-1);
	}
	new_envp[count + 1] = NULL;
	*envp = new_envp;
}

char	**clone_envp_with_special(char **envp)
{
	char	**envp_dup;

	envp_dup = clone_double_array(envp);
	add_to_envp(&envp_dup, "?=0");
	return (envp_dup);
}
