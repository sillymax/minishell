/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:49:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

void	free_subtokennode(t_subtokennode *subtokennode)
{
	if (subtokennode == NULL)
		return ;
	free_subtokennode(subtokennode->next);
	free(subtokennode->subtoken);
	free(subtokennode);
}

void	free_subtokenlist(t_subtokenlist *subtokenlist)
{
	if (subtokenlist == NULL)
		return ;
	free_subtokennode(subtokenlist->head);
	free(subtokenlist);
}

void	free_tokennode(t_tokennode *tokennode)
{
	if (tokennode == NULL)
		return ;
	free_tokennode(tokennode->next);
	free_subtokenlist(tokennode->subtokenlist);
	free(tokennode);
}

void	free_tokenlist(t_tokenlist *tokenlist)
{
	if (tokenlist == NULL)
		return ;
	free_tokennode(tokenlist->head);
	free(tokenlist);
}
