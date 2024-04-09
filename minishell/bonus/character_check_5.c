/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:57:02 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	is_equal(char c)
{
	return (c == '=');
}

bool	is_leftbracket(char c)
{
	return (c == '(');
}

bool	is_rightbracket(char c)
{
	return (c == ')');
}

bool	is_bracket(char c)
{
	return (is_leftbracket(c) || is_rightbracket(c));
}

bool	is_pipe(char c)
{
	return (c == '|');
}
