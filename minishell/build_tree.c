/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:25:04 by ychng             #+#    #+#             */
/*   Updated: 2024/03/30 01:46:41 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_treenode	*build_tree(t_tokenlist *tokenlist)
{
	t_treenode	*cmdlist;
	t_treenode	*opslist;
	t_treenode	*treenode;
	char		*firsubtok;

	cmdlist = NULL;
	opslist = NULL;
	while (tokenlist && tokenlist->head)
	{
		firsubtok = currsubtok_in(tokenlist);
		if (is_leftbracket(firsubtok[0]))
		{
			free_tokennode(pop_tokenlist_head(tokenlist));
			treenode = build_tree(tokenlist);
			push_(treenode, &cmdlist);
		}
		else if (is_rightbracket(firsubtok[0]))
		{
			free_tokennode(pop_tokenlist_head(tokenlist));
			break ;
		}
		else if (is_logicalop(firsubtok))
		{
			if (opslist != NULL)
			{
				treenode = pop_treenode_from(&opslist);
				treenode->right = pop_treenode_from(&cmdlist);
				treenode->left = pop_treenode_from(&cmdlist);
				push_(treenode, &cmdlist);
			}
			treenode = new_treenode(pop_tokenlist_head(tokenlist));
			push_(treenode, &opslist);
		}
		else
		{
			treenode = new_treenode(pop_tokenlist_head(tokenlist));
			push_(treenode, &cmdlist);
		}
	}
	if (opslist != NULL)
	{
		treenode = pop_treenode_from(&opslist);
		treenode->right = pop_treenode_from(&cmdlist);
		treenode->left = pop_treenode_from(&cmdlist);
		push_(treenode, &cmdlist);
	}
	return (pop_treenode_from(&cmdlist));
}
