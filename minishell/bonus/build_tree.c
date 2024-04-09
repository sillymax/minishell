/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:25:04 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static void	handle_leftbracket(t_treenode **cmdlist, \
									t_tokenlist **tokenlist)
{
	t_treenode	*treenode;

	free_tokennode(pop_tokenlist_head(*tokenlist));
	treenode = build_tree(*tokenlist);
	push_(treenode, cmdlist);
}

static void	handle_logicalop(t_treenode **cmdlist, t_treenode **opslist, \
							t_tokenlist **tokenlist)
{
	t_treenode	*treenode;

	if (*opslist != NULL)
	{
		treenode = pop_treenode_from(opslist);
		treenode->right = pop_treenode_from(cmdlist);
		treenode->left = pop_treenode_from(cmdlist);
		push_(treenode, cmdlist);
	}
	treenode = new_treenode(pop_tokenlist_head(*tokenlist));
	push_(treenode, opslist);
}

static void	handle_default(t_treenode **cmdlist, t_tokenlist **tokenlist)
{
	t_treenode	*treenode;

	treenode = new_treenode(pop_tokenlist_head(*tokenlist));
	push_(treenode, cmdlist);
}

static void	empty_opslist(t_treenode **cmdlist, t_treenode **opslist)
{
	t_treenode	*treenode;

	if (*opslist != NULL)
	{
		treenode = pop_treenode_from(opslist);
		treenode->right = pop_treenode_from(cmdlist);
		treenode->left = pop_treenode_from(cmdlist);
		push_(treenode, cmdlist);
	}
}

t_treenode	*build_tree(t_tokenlist *tokenlist)
{
	t_treenode	*cmdlist;
	t_treenode	*opslist;
	char		*firsubtok;

	cmdlist = NULL;
	opslist = NULL;
	while (tokenlist && tokenlist->head)
	{
		firsubtok = currsubtok_in(tokenlist);
		if (is_leftbracket(firsubtok[0]))
			handle_leftbracket(&cmdlist, &tokenlist);
		else if (is_rightbracket(firsubtok[0]))
		{
			free_tokennode(pop_tokenlist_head(tokenlist));
			break ;
		}
		else if (is_logicalop(firsubtok))
			handle_logicalop(&cmdlist, &opslist, &tokenlist);
		else
			handle_default(&cmdlist, &tokenlist);
	}
	empty_opslist(&cmdlist, &opslist);
	return (pop_treenode_from(&cmdlist));
}
