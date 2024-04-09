/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:20:37 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	is_underscore(char c)
{
	return (c == '_');
}

bool	is_hash(char c)
{
	return (c == '#');
}

bool	is_dollar_sign(char c)
{
	return (c == '$');
}

bool	is_asterisk(char c)
{
	return (c == '*');
}

bool	is_ampersand(char c)
{
	return (c == '@');
}
