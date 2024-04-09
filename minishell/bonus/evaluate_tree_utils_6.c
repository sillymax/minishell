/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:50:53 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

t_subtokenlist	*extract_redirection(t_subtokenlist **currcmd)
{
	t_subtokenlist	*cmdlist;
	t_subtokenlist	*redirlist;

	cmdlist = create_subtokenlist();
	redirlist = create_subtokenlist();
	while ((*currcmd)->head)
	{
		if (is_redirection((*currcmd)->head->subtoken))
		{
			link_subtokenlist(pop_subtokenlist_head(*currcmd), redirlist);
			link_subtokenlist(pop_subtokenlist_head(*currcmd), redirlist);
		}
		else
		{
			link_subtokenlist(pop_subtokenlist_head(*currcmd), cmdlist);
		}
	}
	free_subtokenlist(*currcmd);
	*currcmd = cmdlist;
	return (redirlist);
}

int	get_infilefd(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;
	char			*name;
	int				infilefd;

	infilefd = 0;
	current = redirlist->head;
	while (current)
	{
		if (is_heredoc(current->subtoken) || is_infile(current->subtoken))
		{
			if (infilefd != 0)
				close(infilefd);
			name = current->next->subtoken;
			infilefd = open(name, O_RDONLY, 0644);
			if (infilefd == -1)
			{
				printf("%s: No such file or directory\n", name);
				break ;
			}
		}
		current = current->next;
	}
	return (infilefd);
}

int	get_outfilefd(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;
	int				lastfd;
	char			*name;

	lastfd = 0;
	current = redirlist->head;
	while (current)
	{
		if (is_append(current->subtoken) || is_output(current->subtoken))
		{
			name = current->next->subtoken;
			if (is_append(current->subtoken))
				lastfd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (is_output(current->subtoken))
				lastfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (lastfd == -1)
		{
			printf("%s: Is a directory\n", name);
			break ;
		}
		current = current->next;
	}
	return (lastfd);
}
