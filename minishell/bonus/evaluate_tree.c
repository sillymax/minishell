/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:35:54 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static char	*getoperator(t_treenode *node)
{
	t_subtokenlist	*subtokenlist;
	t_subtokennode	*currsub;

	subtokenlist = node->token->subtokenlist;
	currsub = subtokenlist->head;
	return (currsub->subtoken);
}

static bool	evaluate_cmd(t_tokennode *token, char ***envp)
{
	int				prev_pipefd[2];
	t_subtokenlist	*subtokenlist;
	t_subtokenlist	*currcmd;

	ft_bzero(prev_pipefd, sizeof(int) * 2);
	subtokenlist = token->subtokenlist;
	while (subtokenlist->head)
	{
		currcmd = create_subtokenlist();
		while (subtokenlist->head && !is_pipe(*(subtokenlist->head->subtoken)))
			link_subtokenlist(pop_subtokenlist_head(subtokenlist), currcmd);
		exec_cmd(envp, prev_pipefd, &currcmd, !subtokenlist->head);
		if (subtokenlist->head)
			free_subtokennode(pop_subtokenlist_head(subtokenlist));
		free_subtokenlist(currcmd);
	}
	wait_for_forks(*envp);
	return (get_exitstatus(*envp) == 0);
}

bool	evaluate_tree(t_treenode *root, char ***envp)
{
	bool	left;

	if (root == NULL)
		return (false);
	left = evaluate_tree(root->left, envp);
	if (!ft_strcmp(getoperator(root), "&&"))
	{
		if (left == false)
			return (false);
		return (evaluate_tree(root->right, envp));
	}
	else if (!ft_strcmp(getoperator(root), "||"))
	{
		if (left == false)
			return (evaluate_tree(root->right, envp));
	}
	return (evaluate_cmd(root->token, envp));
}
