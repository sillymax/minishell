/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 03:07:57y ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	read_content(t_subtokenlist *currcmd, int tmpfd)
{
	char	*name;
	char	*readline;

	name = ft_strjoin(currcmd->head->subtoken, "\n", "");
	readline = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (!ft_strncmp(readline, name, ft_strlen(readline)))
			break ;
		write(tmpfd, readline, ft_strlen(readline));
		free(readline);
		readline = get_next_line(STDIN_FILENO);
	}
	free(name);
	free(readline);
}

char	*create_tmpfile(t_subtokenlist *currcmd)
{
	static int	count;
	char		*numb;
	char		*name;
	int			tmpfd;

	numb = ft_itoa(count);
	name = ft_strjoin("heredocs/temp_", ".txt", numb);
	count++;
	free(numb);
	tmpfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmpfd == -1)
	{
		printf("open failed for tmpfd\n");
		free(name);
		exit(-1);
	}
	read_content(currcmd, tmpfd);
	close(tmpfd);
	return (name);
}

int	count_heredocs(t_subtokenlist *currcmd)
{
	int				count;
	t_subtokennode	*current;

	count = 0;
	current = currcmd->head;
	while (current)
	{
		if (is_heredoc(current->subtoken))
			count++;
		current = current->next;
	}
	return (count);
}

void	expand_heredocs(t_subtokenlist **currcmd)
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
			if (heredoc_count == count)
			{
				link_subtokenlist(new_subtokennode(ft_strdup("<<")), result);
				link_subtokenlist(new_subtokennode(heredoc), result);
			}
			else
				free(heredoc);
			free_subtokennode(pop_subtokenlist_head(*currcmd));
		}
		else
			link_subtokenlist(pop_subtokenlist_head(*currcmd), result);
	}
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
