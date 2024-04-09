/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:38:57 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

char	*currsubtok_in(t_tokenlist *tokenlist)
{
	t_subtokenlist	*subtokenlist;
	char			*subtoken;

	subtokenlist = tokenlist->head->subtokenlist;
	subtoken = subtokenlist->head->subtoken;
	return (subtoken);
}

t_treenode	*pop_treenode_from(t_treenode **list)
{
	t_treenode	*popnode;
	t_treenode	*current;

	if (*list == NULL)
		return (NULL);
	if ((*list)->next == NULL)
	{
		popnode = *list;
		*list = NULL;
		return (popnode);
	}
	popnode = getlastnode(*list);
	current = *list;
	while (current->next->next != NULL)
		current = current->next;
	current->next = NULL;
	return (popnode);
}

t_treenode	*new_treenode(t_tokennode *tokennode)
{
	t_treenode	*newnode;

	newnode = malloc(1 * sizeof(t_treenode));
	if (newnode == NULL)
	{
		printf("malloc failed for newnode\n");
		exit(-1);
	}
	newnode->token = tokennode;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->next = NULL;
	return (newnode);
}

void	push_(t_treenode *cmdnode, t_treenode **cmdlist)
{
	t_treenode	*tail;

	if (*cmdlist == NULL)
		*cmdlist = cmdnode;
	else
	{
		tail = getlastnode(*cmdlist);
		tail->next = cmdnode;
	}
}
