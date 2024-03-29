/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:32:23 by ychng             #+#    #+#             */
/*   Updated: 2024/03/30 01:46:10 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Don't need to free subtoken in here,
// Becase i'm passing it as a pointer for subtokennode->subtoken
// So it will be freed in free_tokenlist.c instead
static t_subtokenlist	*get_subtokenlist(char *token, char **envp)
{
	t_subtokenlist	*subtokenlist;
	char			*subtoken;
	bool			expand_heredoc;

	subtokenlist = create_subtokenlist();
	if (is_logicalop(token))
	{
		subtoken = ft_strdup(token);
		link_subtokenlist(new_subtokennode(subtoken), subtokenlist);
	}
	else
	{
		subtoken = get_next_subtoken(token);
		expand_heredoc = false;
		while (subtoken)
		{
			subtoken = expand_subtoken(subtoken, expand_heredoc, envp);
			if (is_heredoc(subtoken) || expand_heredoc == true)
				expand_heredoc = !expand_heredoc;
			link_subtokenlist(new_subtokennode(subtoken), subtokenlist);
			subtoken = get_next_subtoken(NULL);
		}
	}
	return (subtokenlist);
}

t_tokenlist	*get_tokenlist(char *input, char **envp)
{
	t_tokenlist		*tokenlist;
	t_tokennode		*tokennode;
	char			*token;

	if (input == NULL)
		return (NULL);
	tokenlist = create_tokenlist();
	token = get_next_token(input, true);
	while (token)
	{
		if (ft_strspn(token, " ") != ft_strlen(token))
		{
			tokennode = create_tokennode(get_subtokenlist(token, envp));
			link_tokenlist(tokennode, tokenlist);
		}
		free(token);
		token = get_next_token(NULL, true);
	}
	return (tokenlist);
}
