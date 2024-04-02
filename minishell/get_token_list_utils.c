/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:32:32 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 18:25:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_subtoken(char *subtoken, bool expand_heredoc, char **envp)
{
	if (expand_heredoc)
	{
		subtoken = expand_escaped(subtoken);
	}
	else
	{
		subtoken = expand_tilde(subtoken);
		subtoken = expand_env(subtoken, envp);
		subtoken = expand_quotes(subtoken, ft_strlen(subtoken));
		subtoken = expand_escaped(subtoken);
	}
	return (subtoken);
}
