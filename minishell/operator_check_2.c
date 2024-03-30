/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:39 by ychng             #+#    #+#             */
/*   Updated: 2024/03/31 05:09:57 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_append(char *str)
{
	return (ft_strcmp(str, ">>") == 0);
}

bool	is_output(char *str)
{
	return (ft_strcmp(str, ">") == 0);
}
