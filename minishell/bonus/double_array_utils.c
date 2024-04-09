/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:04:33 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	count_2d_array_items(char **double_array)
{
	int	count;

	count = 0;
	while (double_array[count])
		count++;
	return (count);
}

char	**clone_double_array(char **double_array)
{
	int		items_count;
	char	**result;
	int		i;

	items_count = count_2d_array_items(double_array) + 1;
	result = malloc(sizeof(char *) * items_count);
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = -1;
	while (double_array[++i])
	{
		result[i] = ft_strdup(double_array[i]);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
		}
	}
	result[i] = NULL;
	return (result);
}

void	free_double_array(char **double_array)
{
	int	i;

	i = -1;
	while (double_array[++i])
		free(double_array[i]);
	free(double_array);
}
