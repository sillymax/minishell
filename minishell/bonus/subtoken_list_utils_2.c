/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtokenlist_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:19:44 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 18:20:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	count_subtokenlist(t_subtokenlist *subtokenlist)
{
	int				count;
	t_subtokennode	*current;

	count = 0;
	current = subtokenlist->head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
