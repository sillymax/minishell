/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:08:02 by ychng             #+#    #+#             */
/*   Updated: 2024/03/29 16:19:32 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*format_joininput(char *joininput)
{
	if (*joininput == '\0')
	{
		free(joininput);
		return (ft_strdup("\n"));
	}
	return (joininput);
}
