/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:25 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 05:48:37 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_list(t_tokenlist *tokenlist)
{
	t_tokennode		*currtok;
	t_subtokennode	*currsub;

	currtok = tokenlist->head;
	while (currtok)
	{
		currsub = currtok->subtokenlist->head;
		while (currsub)
		{
			printf("%s\n", currsub->subtoken);
			currsub = currsub->next;
		}
		printf("\n");
		currtok = currtok->next;
	}
}

void	print_treenode(t_treenode *root)
{
	t_tokennode		*currtok;
	t_subtokennode	*currsub;

	if (root == NULL)
		return ;
	currtok = root->token;
	currsub = currtok->subtokenlist->head;
	while (currsub)
	{
		printf("%s\n", currsub->subtoken);
		currsub = currsub->next;
	}
	printf("\n");
	printf("Left: ");
	print_treenode(root->left);
	printf("Right: ");
	print_treenode(root->right);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_tokenlist	*tokenlist;
	t_treenode	*root;

	((void)argc, (void)argv);
	envp = clone_envp_with_special(envp);
	while (1)
	{
		input = read_inputline();
		tokenlist = get_tokenlist(input, envp);
		root = build_tree(tokenlist);
		evaluate_heredocs(root);
		evaluate_tree(root, &envp);
		// tokenlist = infix_to_postfix(tokenlist);
		// evaluate_postfix(&envp, tokenlist);
		// print_list(tokenlist);
		free(input);
		free_tokenlist(tokenlist);
	}
}
