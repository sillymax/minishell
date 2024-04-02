/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:41:55 by ychng             #+#    #+#             */
/*   Updated: 2024/04/02 17:46:49 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_backslash(char c)
{
	return (c == '\\');
}

bool	is_singquote(char c)
{
	return (c == '\'');
}

bool	is_doubquote(char c)
{
	return (c == '\"');
}

bool	is_quote(char c)
{
	return (is_singquote(c) || is_doubquote(c));
}

bool	is_delim(char c, char *delim)
{
	return (ft_strchr(delim, c));
}
