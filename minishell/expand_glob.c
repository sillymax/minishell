/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:03 by ychng             #+#    #+#             */
/*   Updated: 2024/04/03 20:50:10 by ychng            ###   ########.fr       */
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

int	get_dirsize(void)
{
	DIR				*dp;
	int				count;
	struct dirent	*entry;

	dp = opendir(".");
	if (dp == -1)
	{
		printf("opendir failed for dp\n");
		exit(-1);
	}
	count = 0;
	entry = readdir(dp);
	while (entry != NULL)
	{
		count++;
		entry = readdir(dp);
	}
	close(dp);
	return (count);
}

char	*handle_globexpansion(void)
{
	DIR				*dp;
	int				count;
	struct dirent	*entry;
	char			*result;
	char			*prevresult;

	dp = opendir(".");
	if (dp == NULL)
	{
		printf("opendir failed for dp\n");
		exit(-1);
	}
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

char	*expand_glob(char *subtoken)
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
		return (result);
	}
	return (subtoken);
}
