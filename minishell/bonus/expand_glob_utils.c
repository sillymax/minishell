/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:47:12 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

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
	if (inquote)
		return (0);
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
	if (inquote)
		return (ft_strlen(subtoken));
	return (end);
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
