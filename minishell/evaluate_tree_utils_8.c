/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tree_utils_8.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:13:24 by ychng             #+#    #+#             */
/*   Updated: 2024/04/06 16:31:32 by ychng            ###   ########.fr       */
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

	if (is_invalid_filename(bin))
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ":");
		while (path)
		{
			if (bin[0] == '.' || bin[0] == '/')
				full_path = ft_strjoin(bin, "", "");
			else
				full_path = ft_strjoin(path, bin, "/");
			if (is_executable(full_path) && access(full_path, X_OK) == 0)
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
		if (!ft_strcmp(args[0], "."))
			printf("%s: filename argument required\n", args[0]);
		else if (ft_strchr(args[0], '/') && !has_alpha(args[0]))
			printf("%s: is a directory\n", args[0]);
		else if (ft_strchr(args[0], '/'))
			printf("%s: No such file or directory\n", args[0]);
		else if (ft_strlen(args[0]) == 0)
			printf("\'\': command not found\n");
		else
			printf("%s: command not found\n", args[0]);
		free_double_array(args);
		return (-1);
	}
	execve(bin, args, envp);
	free_double_array(args);
	return (-1);
}
