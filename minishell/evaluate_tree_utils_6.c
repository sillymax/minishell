/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:13:24 by ychng             #+#    #+#             */
/*   Updated: 2024/04/01 08:01:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	**currcmd_to_2d_array(t_subtokenlist *currcmd)
{
	char			**result;
	t_subtokennode	*current;
	int				i;

	result = malloc(sizeof(char *) * (count_subtokenlist(currcmd) + 1));
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = 0;
	current = currcmd->head;
	while (current)
	{
		result[i] = ft_strdup(current->subtoken);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
		}
		i++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

static char	*find_full_bin_path(char *bin, char **envp)
{
	int		i;
	char	*path;
	char	*full_path;

	if (access(bin, F_OK) == 0)
		return (bin);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ":");
		while (path)
		{
			full_path = ft_strjoin(path, bin, "/");
			if (access(full_path, F_OK) == 0)
				return (full_path);
			free(full_path);
			path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

int	run_execve(char **envp, t_subtokenlist *currcmd)
{
	char	**args;
	char	*bin;

	args = currcmd_to_2d_array(currcmd);
	bin = find_full_bin_path(args[0], envp);
	if (bin == NULL)
	{
		printf("%s: command not found\n", args[0]);
		free_double_array(args);
		return (-1);
	}
	execve(bin, args, envp);
	free_double_array(args);
	return (-1);
}
