/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:34:29 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 14:34:59 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// I can't find the solution for ctrl+c
// if i add this line i get weird double prompt
// rl_redisplay(); main> main>
// if I remove it I get normal prompt
// But i have to interact with any keys for it to appear
// I choose the latter one
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
