/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static void	expand_heredocs(t_subtokenlist **currcmd, char **envp)
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
			heredoc = create_tmpfile(*currcmd, envp);
			manage_heredoc(result, heredoc, heredoc_count, count);
			free_subtokennode(pop_subtokenlist_head(*currcmd));
		}
		else
			link_subtokenlist(pop_subtokenlist_head(*currcmd), result);
	}
	free_subtokenlist(*currcmd);
	*currcmd = result;
}

void	evaluate_heredocs(t_treenode *root, char **envp)
{
	if (root == NULL)
		return ;
	if (root->left == NULL && root->right == NULL)
		expand_heredocs(&root->token->subtokenlist, envp);
	evaluate_heredocs(root->left, envp);
	evaluate_heredocs(root->right, envp);
}
