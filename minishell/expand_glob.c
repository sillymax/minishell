/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/04 19:45:58 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	trim_frontemptyquotes(char *subtoken)
{
	int		start;
	bool	inquote;
	char	quote_type;

	start = 0;
	inquote = false;
	quote_type = '\0';
	while (is_quote(subtoken[start]))
	{
		if (inquote == false)
			toggle_inquote(subtoken[start], &inquote, &quote_type);
		else if (inquote && (quote_type == subtoken[start]))
			toggle_inquote(subtoken[start], &inquote, &quote_type);
		else if (inquote == true)
			break ;
		start++;
	}
	return (start);
}

int	trim_backemptyquotes(char *subtoken)
{
	int		end;
	bool	inquote;
	char	quote_type;

	end = ft_strlen(subtoken);
	inquote = false;
	quote_type = '\0';
		while (end > 0 && is_quote(subtoken[end - 1]))
	{
		if (inquote == false)
			toggle_inquote(subtoken[end - 1], &inquote, &quote_type);
		else if (inquote && (quote_type == subtoken[end]))
			toggle_inquote(subtoken[end - 1], &inquote, &quote_type);
		else if (inquote == true)
			break ;
		end--;
	}
	return (end);
}

char	*trim_emptyquotes(char *subtoken)
{
	int		start;
	int		end;
	char	*result;

	start = trim_frontemptyquotes(subtoken);
	end = trim_backemptyquotes(subtoken);
	result = ft_substr(subtoken, start, end);
	return (result);	
}

DIR	*get_dp(char *path)
{
	DIR	*dp;

	dp = opendir(path);
	if (dp == NULL)
	{
		printf("opendir failed for dp\n");
		exit(-1);
	}
	return (dp);
}

int	get_dirsize(void)
{
	DIR				*dp;
	int				count;
	struct dirent	*entry;

	dp = get_dp(".");
	count = 0;
	entry = readdir(dp);
	while (entry != NULL)
	{
		count++;
		entry = readdir(dp);
	}
	closedir(dp);
	return (count);
}

char	*handle_globexpansion(void)
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

// I pop the last node so that the link subtokenlist outside can till work normally
// if not i add an extra "" empty string
char	*link_entries(char *result, t_subtokenlist *subtokenlist)
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
		result = handle_globexpansion();
		return (link_entries(result, subtokenlist));
	}
	return (subtoken);
}
