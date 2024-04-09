/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:39 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

bool	is_append(char *str)
{
	return (ft_strcmp(str, ">>") == 0);
}

bool	is_output(char *str)
{
	return (ft_strcmp(str, ">") == 0);
}

bool	is_infile(char *str)
{
	return (ft_strcmp(str, "<") == 0);
}
