/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:47:46 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

void	toggle_inquote(char c, bool *inquote, char *quote_type)
{
	if (*inquote == false)
	{
		*inquote = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*inquote = false;
		*quote_type = '\0';
	}
}
