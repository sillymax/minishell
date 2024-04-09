/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

static char	*trim_emptyquotes(char *subtoken)
{
	int		start;
	int		end;
	char	*result;

	start = trim_frontemptyquotes(subtoken);
	end = trim_backemptyquotes(subtoken);
	if (start > end)
		result = ft_strdup(subtoken);
	else
		result = ft_substr(subtoken, start, end);
	return (result);
}

static char	*handle_globexpansion(void)
{
	DIR				*dp;
	int				count;
	struct dirent	*entry;
	char			*result;

	dp = get_dp(".");
	result = NULL;
	count = get_dirsize();
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", 1) != 0)
		{
			result = custom_strjoin(result, entry->d_name);
			if (count != 0)
				result = custom_strjoin(result, " ");
		}
		count--;
		entry = readdir(dp);
	}
	closedir(dp);
	return (result);
}

// I popped the last node
// so that expand_subtoken
// can still work after glob
// if not it will create an empty str ""
static char	*link_entries(char *result, t_subtokenlist *subtokenlist)
{
	char	*subtoken;

	subtoken = ft_strtok(result, " ");
	while (subtoken)
	{
		link_subtokenlist(new_subtokennode(ft_strdup(subtoken)), subtokenlist);
		subtoken = ft_strtok(NULL, " ");
	}
	subtoken = ft_strdup(subtokenlist->tail->subtoken);
	free_subtokennode(pop_subtokenlist_tail(subtokenlist));
	free(result);
	return (subtoken);
}

char	*expand_glob(char *subtoken, t_subtokenlist *subtokenlist)
{
	char	*trimmedquotes;
	char	*trimmedglobs;
	char	*result;

	trimmedquotes = trim_emptyquotes(subtoken);
	trimmedglobs = ft_strtrim(trimmedquotes, "*");
	free(trimmedquotes);
	if (trimmedglobs == NULL)
	{
		free(subtoken);
		free(trimmedglobs);
		result = handle_globexpansion();
		return (link_entries(result, subtokenlist));
	}
	free(trimmedglobs);
	return (subtoken);
}
