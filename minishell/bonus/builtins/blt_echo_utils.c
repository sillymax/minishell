/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:38:02 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

bool	is_n_options(char *subtoken)
{
	if (ft_strncmp(subtoken, "-n", 2) == 0)
	{
		subtoken += 2;
		subtoken += ft_strspn(subtoken, "n");
		if (*subtoken == '\0')
			return (true);
	}
	return (false);
}

t_subtokennode	*find_first_non_option(t_subtokennode *args)
{
	while (args)
	{
		if (is_n_options(args->subtoken) == false)
			return (args);
		args = args->next;
	}
	return (NULL);
}
