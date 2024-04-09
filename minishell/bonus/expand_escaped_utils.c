/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:04 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	should_escape(char quote_type, char *subtoken)
{
	if (is_singquote(quote_type) || !is_backslash(*subtoken))
		return (false);
	if (is_doubquote(quote_type) && is_escapable(*(subtoken + 1)))
		return (true);
	if (!is_doubquote(quote_type))
		return (true);
	return (false);
}
