/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static char	*handle_maininput(char **envp)
{
	bool	firstiter;
	char	*maininput;

	firstiter = true;
	maininput = NULL;
	while (firstiter || *maininput == '\0')
	{
		free(maininput);
		firstiter = false;
		maininput = readline("main> ");
		if (maininput == NULL)
		{
			printf("exit\n");
			free_double_array(envp);
			exit(-1);
		}
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			update_exit_status(envp, 130);
		}
	}
	return (maininput);
}

// Lazy to write another function
// So I tried a different method
// Which is to redirect to /dev/null
// Because has_noerror will print to stdout
static char	*handle_errortrim(char *input)
{
	int	original_stdout;
	int	null_fd;

	original_stdout = dup_stdoutfd(input);
	null_fd = dup_nullfd(input);
	dup2(null_fd, STDOUT_FILENO);
	if (!has_noerror(input))
		input = trim_errorpart(input);
	dup2(original_stdout, STDOUT_FILENO);
	close(null_fd);
	close(original_stdout);
	return (input);
}

static void	update_history(char *input)
{
	static char	*previnput;

	if (previnput && !ft_strcmp(previnput, input) && !contains_newline(input))
		return ;
	if (previnput != NULL)
		free(previnput);
	previnput = ft_strdup(input);
	if (!previnput)
	{
		printf("ft_strdup failed for previnput\n");
		exit(-1);
	}
	add_history(previnput);
}

char	*read_inputline(char **envp)
{
	char	*input;

	input = handle_maininput(envp);
	update_history(input);
	while (has_noerror(input) && has_openblock(input))
	{
		input = closequotes(input, envp);
		if (!has_noerror(input))
			break ;
		input = closebrackets(input, envp);
		if (!has_noerror(input))
			break ;
		input = closelogicalops(input, envp);
		update_history(input);
	}
	input = handle_errortrim(input);
	return (input);
}
