/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_heredocs_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:19:34 by ychng             #+#    #+#             */
/*   Updated: 2024/04/09 14:14:07 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Didn't expand escaped cause need to remeber last input
// example \\\n if the n is on new line
static void	read_content(t_subtokenlist *currcmd, int tmpfd, char **envp)
{
	char	*name;
	char	*input;

	name = ft_strjoin(currcmd->head->subtoken, "\n", "");
	input = readline("docs> ");
	while (g_sig == 0)
	{
		if (!ft_strncmp(input, name, ft_strlen(input)))
			break ;
		input = expand_env(input, envp);
		write(tmpfd, input, ft_strlen(input));
		write(tmpfd, "\n", 1);
		free(input);
		input = readline("docs> ");
	}
	free(name);
	free(input);
	if (g_sig == SIGINT)
		update_exit_status(envp, 130);
}

char	*create_tmpfile(t_subtokenlist *currcmd, char **envp)
{
	static int	count;
	char		*numb;
	char		*name;
	int			tmpfd;

	numb = ft_itoa(count);
	name = ft_strjoin("heredocs/temp_", ".txt", numb);
	count++;
	free(numb);
	tmpfd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmpfd == -1)
	{
		printf("open failed for tmpfd\n");
		free(name);
		exit(-1);
	}
	read_content(currcmd, tmpfd, envp);
	close(tmpfd);
	return (name);
}
