/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:18:51 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	count_heredocs(t_subtokenlist *currcmd)
{
	int				count;
	t_subtokennode	*current;

	count = 0;
	current = currcmd->head;
	while (current)
	{
		if (is_heredoc(current->subtoken))
			count++;
		current = current->next;
	}
	return (count);
}

void	manage_heredoc(t_subtokenlist *result, char *heredoc, \
					int heredoc_count, int count)
{
	if (heredoc_count == count)
	{
		link_subtokenlist(new_subtokennode(ft_strdup("<<")), result);
		link_subtokenlist(new_subtokennode(heredoc), result);
	}
	else
		free(heredoc);
}
