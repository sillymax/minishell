/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 01:33:29 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	expand_heredocs(t_subtokenlist **currcmd)
{
	t_subtokenlist	*result;
	char			*heredoc;
	int				heredoc_count;
	int				count;

	count = 0;
	heredoc_count = count_heredocs(*currcmd);
	result = create_subtokenlist();
	while ((*currcmd)->head)
	{
		if (is_heredoc((*currcmd)->head->subtoken))
		{
			free_subtokennode(pop_subtokenlist_head(*currcmd));
			count++;
			heredoc = create_tmpfile(*currcmd);
			manage_heredoc(result, heredoc, heredoc_count, count);
			free_subtokennode(pop_subtokenlist_head(*currcmd));
		}
		else
			link_subtokenlist(pop_subtokenlist_head(*currcmd), result);
	}
	free_subtokenlist(*currcmd);
	*currcmd = result;
}

void	evaluate_heredocs(t_treenode *root)
{
	if (root == NULL)
		return ;
	if (root->left == NULL && root->right == NULL)
		expand_heredocs(&root->token->subtokenlist);
	evaluate_heredocs(root->left);
	evaluate_heredocs(root->right);
}
