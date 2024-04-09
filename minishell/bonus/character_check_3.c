/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:21:37 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	is_question_mark(char c)
{
	return (c == '?');
}

bool	is_exclamation(char c)
{
	return (c == '!');
}

bool	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_uppercase(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool	is_lowercase(char c)
{
	return (c >= 'a' && c <= 'z');
}
