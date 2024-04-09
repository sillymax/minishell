/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtokenlist_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:25:10 by ychng             #+#    #+#             */
/*   Updated: 2024/03/20 17:00:10 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

t_subtokennode	*new_subtokennode(char *subtoken)
{
	t_subtokennode	*subtokennode;

	subtokennode = malloc(sizeof(t_subtokennode));
	if (!subtokennode)
	{
		printf("malloc failed for subtokennode\n");
		exit(-1);
	}
	subtokennode->subtoken = subtoken;
	subtokennode->next = NULL;
	subtokennode->prev = NULL;
	return (subtokennode);
}

t_subtokenlist	*create_subtokenlist(void)
{
	t_subtokenlist	*subtokenlist;

	subtokenlist = malloc(sizeof(t_subtokenlist));
	if (!subtokenlist)
	{
		printf("malloc failed for subtokenlist\n");
		exit(-1);
	}
	subtokenlist->head = NULL;
	subtokenlist->tail = NULL;
	return (subtokenlist);
}

t_subtokennode	*pop_subtokenlist_head(t_subtokenlist *subtokenlist)
{
	t_subtokennode	*popnode;
	t_subtokennode	*newhead;

	if (subtokenlist == NULL || subtokenlist->head == NULL)
		return (NULL);
	popnode = subtokenlist->head;
	newhead = popnode->next;
	if (newhead == NULL)
	{
		subtokenlist->head = NULL;
		subtokenlist->tail = NULL;
	}
	else
	{
		popnode->next = NULL;
		newhead->prev = NULL;
		subtokenlist->head = newhead;
	}
	return (popnode);
}

t_subtokennode	*pop_subtokenlist_tail(t_subtokenlist *subtokenlist)
{
	t_subtokennode	*popnode;
	t_subtokennode	*newtail;

	if (subtokenlist == NULL || subtokenlist->tail == NULL)
		return (NULL);
	popnode = subtokenlist->tail;
	newtail = popnode->prev;
	if (newtail == NULL)
	{
		subtokenlist->head = NULL;
		subtokenlist->tail = NULL;
	}
	else
	{
		popnode->prev = NULL;
		newtail->next = NULL;
		subtokenlist->tail = newtail;
	}
	return (popnode);
}

void	link_subtokenlist(t_subtokennode *subtokennode, \
			t_subtokenlist *subtokenlist)
{
	if (subtokenlist->head == NULL)
	{
		subtokenlist->head = subtokennode;
		subtokenlist->tail = subtokennode;
	}
	else
	{
		while (subtokenlist->tail->next)
			subtokenlist->tail = subtokenlist->tail->next;
		subtokenlist->tail->next = subtokennode;
		subtokennode->prev = subtokenlist->tail;
		subtokenlist->tail = subtokennode;
	}
}
