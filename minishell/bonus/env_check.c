/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:23:55 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	is_special_env_name(char c)
{
	return (is_number(c)
		|| (is_hash(c))
		|| (is_asterisk(c))
		|| (is_ampersand(c))
		|| (is_dollar_sign(c))
		|| (is_exclamation(c))
		|| (is_question_mark(c)));
}

bool	is_valid_env_name(char c)
{
	return (is_underscore(c)
		|| (is_uppercase(c))
		|| (is_lowercase(c))
		|| (is_number(c)));
}

bool	is_env_var(char *remaining_input)
{
	return ((is_dollar_sign(*remaining_input))
		&& (is_valid_env_name(*(remaining_input + 1))
			|| is_special_env_name(*(remaining_input + 1))));
}
