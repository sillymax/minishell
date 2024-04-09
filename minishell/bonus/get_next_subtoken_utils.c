/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_subtoken_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:53:19 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	len_of_redirection(char *subtoken)
{
	if (ft_strncmp(subtoken, "<<<", 3) == 0)
		return (3);
	else if (ft_strncmp(subtoken, "<<", 2) == 0
		|| ft_strncmp(subtoken, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(subtoken, "<", 1) == 0
		|| ft_strncmp(subtoken, ">", 1) == 0
		|| ft_strncmp(subtoken, "|", 1) == 0)
		return (1);
	return (0);
}

bool	is_space_or_redirection(char *subtoken)
{
	return (is_space(*subtoken) || is_redirection_n(subtoken));
}
