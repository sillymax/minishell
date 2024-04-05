/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:25 by ychng             #+#    #+#             */
/*   Updated: 2024/04/06 04:39:57 by ychng            ###   ########.fr       */
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

void	free_tree(t_treenode *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free_tokennode(root->token);
	free(root);
}

// I can't find the solution for ctrl+c
// if i add this line i get weird double prompt
// rl_redisplay(); main> main>
// if I remove it I get normal prompt
// But i have to interact with any keys for it to appear
// I choose the latter one
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		global_sig = sig;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_tokenlist	*tokenlist;
	t_treenode	*root;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	((void)argc, (void)argv);
	envp = clone_envp_with_special(envp);
	while (1)
	{
		input = read_inputline(envp);
		tokenlist = get_tokenlist(input, envp);
		root = build_tree(tokenlist);
		evaluate_heredocs(root, envp);
		evaluate_tree(root, &envp);
		free(input);
		free_tokenlist(tokenlist);
		free_tree(root);
	}
}
