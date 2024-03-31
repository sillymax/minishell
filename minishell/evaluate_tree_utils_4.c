/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:50:53 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 06:49:38 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

int	get_outfilefd(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;
	int				lastfd;
	char			*name;

	lastfd = 0;
	current = redirlist->head;
	while (current)
	{
		if (is_append(current->subtoken))
		{
			name = current->next->subtoken;
			lastfd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (is_output(current->subtoken))
		{
			name = current->next->subtoken;
			lastfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (lastfd == -1)
		{
			printf("open failed for lastfd\n");
			exit(-1);
		}
		current = current->next;
	}
	return (lastfd);
}

void	manage_redirection(t_subtokenlist *redirlist)
{
	t_subtokennode	*current;

	current = redirlist->head;
	while (current)
	{
		if (is_heredoc(current->subtoken))
		{
			int	tmp_fd;
		
			tmp_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (tmp_fd == -1)
			{
				printf("open failed for tmp_fd\n");
				exit(-1);
			}
			char	*name;
			char	*nextline;
		
			name = ft_strjoin(current->next->subtoken, "\n", "");
			nextline = get_next_line(STDIN_FILENO);
			while (1)
			{
				if (!ft_strncmp(name, nextline, ft_strlen(nextline)))
				{
					free(nextline);
					break ;
				}
				write(tmp_fd, nextline, ft_strlen(nextline));
				free(nextline);
				nextline = get_next_line(STDIN_FILENO);
			}
			free(name);
			// dup2(tmp_fd, STDIN_FILENO);
			// close(tmp_fd);
		}
		current = current->next;		
	}	
}
