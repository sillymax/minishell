/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:19 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

// If str is empty set by blt_unset,
// first if condition will return false
bool	has_proper_syntax(char *envp)
{
	char	*equal_ptr;

	if (is_special_env_name(*envp))
		return (false);
	equal_ptr = ft_strchr(envp, '=');
	if (equal_ptr == NULL || equal_ptr == envp)
		return (false);
	return (true);
}

int	blt_env(char **envp)
{
	while (*envp)
	{
		if (has_proper_syntax(*envp))
			printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	envp[0] = "";
// 	blt_env(envp);
// }