/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:44:37 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static char	**create_output(int items_count)
{
	char	**output;

	output = malloc(sizeof(char *) * items_count);
	if (!output)
	{
		printf("malloc failed for output\n");
		exit(-1);
	}
	return (output);
}

static void	count_sort(char **envp, int items_count, int pos)
{
	char	**output;
	int		count[256];
	int		i;

	ft_bzero(count, sizeof(int) * 256);
	i = 0;
	while (i < items_count)
	{
		count[(unsigned char)envp[i][pos]]++;
		i++;
	}
	i = 1;
	while (i < 256)
	{
		count[i] += count[i - 1];
		i++;
	}
	output = create_output(items_count);
	i = items_count;
	while (i--)
		output[--count[(unsigned char)envp[i][pos]]] = envp[i];
	ft_memcpy(envp, output, sizeof(char *) * items_count);
	free(output);
}

void	radix_sort(char **envp)
{
	int	last_pos;
	int	items_count;

	last_pos = get_max_env_name_len(envp);
	while (last_pos--)
	{
		items_count = count_2d_array_items(envp);
		count_sort(envp, items_count, last_pos);
	}
}
