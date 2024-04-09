/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:20:21 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

char	*closequotes(char *input, char **envp)
{
	char	*joininput;

	if (has_openquotes(input) == true)
	{
		input = custom_strjoin(input, "\n");
		joininput = readline("join> ");
		if (!joininput)
		{
			printf("syntax error: unexpected end of file\n");
			free(input);
			free_double_array(envp);
			exit(-1);
		}
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			update_exit_status(envp, 130);
		}
		joininput = format_joininput(joininput);
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

static char	*process_input(char *input, char *joininput, char **envp)
{
	char	*triminput;

	triminput = ft_strtrim(input, "\n");
	free(input);
	input = triminput;
	if (*joininput != '\0')
		input = custom_strjoin(input, " ");
	input = custom_strjoin(input, joininput);
	input = closequotes(input, envp);
	free(joininput);
	return (input);
}

char	*closebrackets(char *input, char **envp)
{
	char	*joininput;

	if (has_openbrackets(input) == true)
	{
		joininput = readline("join> ");
		if (joininput == NULL)
		{
			printf("syntax error: unexpected end of file\n");
			free(input);
			free_double_array(envp);
			exit(-1);
		}
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			update_exit_status(envp, 130);
		}
		input = process_input(input, joininput, envp);
	}
	return (input);
}

char	*closelogicalops(char *input, char **envp)
{
	char	*joininput;

	if (has_openlogicalops(input) == true)
	{
		joininput = readline("join> ");
		if (joininput == false)
		{
			printf("syntax error: unexpected end of file\n");
			free(input);
			free_double_array(envp);
			exit(-1);
		}
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			update_exit_status(envp, 130);
		}
		if (*joininput != '\0')
		{
			input = custom_strjoin(input, " ");
			input = custom_strjoin(input, joininput);
		}
		free(joininput);
	}
	return (input);
}
