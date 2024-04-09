/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:38 by ychng             #+#    #+#             */
/*   Updated: 2024/03/23 00:36:06 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

t_tokennode	*create_tokennode(t_subtokenlist *subtokenlist)
{
	t_tokennode	*tokennode;

	tokennode = malloc(sizeof(t_tokennode));
	if (!tokennode)
	{
		printf("malloc failed for tokennode\n");
		exit(-1);
	}
	tokennode->subtokenlist = subtokenlist;
	tokennode->next = NULL;
	tokennode->prev = NULL;
	return (tokennode);
}

t_tokenlist	*create_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = malloc(sizeof(t_tokenlist));
	if (!tokenlist)
	{
		printf("malloc failed for tokenlist\n");
		exit(-1);
	}
	tokenlist->head = NULL;
	tokenlist->tail = NULL;
	return (tokenlist);
}

t_tokennode	*pop_tokenlist_head(t_tokenlist *tokenlist)
{
	t_tokennode	*popnode;
	t_tokennode	*newhead;

	if (tokenlist == NULL || tokenlist->head == NULL)
		return (NULL);
	popnode = tokenlist->head;
	newhead = popnode->next;
	if (newhead == NULL)
	{
		tokenlist->head = NULL;
		tokenlist->tail = NULL;
	}
	else
	{
		popnode->next = NULL;
		newhead->prev = NULL;
		tokenlist->head = newhead;
	}
	return (popnode);
}

t_tokennode	*pop_tokenlist_tail(t_tokenlist *tokenlist)
{
	t_tokennode	*popnode;
	t_tokennode	*newtail;

	if (tokenlist == NULL || tokenlist->tail == NULL)
		return (NULL);
	popnode = tokenlist->tail;
	newtail = popnode->prev;
	if (newtail == NULL)
	{
		tokenlist->head = NULL;
		tokenlist->tail = NULL;
	}
	else
	{
		popnode->prev = NULL;
		newtail->next = NULL;
		tokenlist->tail = newtail;
	}
	return (popnode);
}

void	link_tokenlist(t_tokennode *tokennode, t_tokenlist *tokenlist)
{
	if (tokenlist->head == NULL)
	{
		tokenlist->head = tokennode;
		tokenlist->tail = tokennode;
	}
	else
	{
		tokenlist->tail->next = tokennode;
		tokennode->prev = tokenlist->tail;
		tokenlist->tail = tokennode;
	}
}
