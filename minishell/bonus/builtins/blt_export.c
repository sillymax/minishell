/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:15:48 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static void	insert_valid_args(char ***envp, t_subtokennode *args)
{
	int	envp_count;
	int	valid_args_count;
	int	old_size;
	int	new_size;

	envp_count = count_2d_array_items(*envp);
	valid_args_count = count_valid_args(*envp, args);
	old_size = sizeof(char *) * (envp_count + 1);
	new_size = sizeof(char *) * (envp_count + valid_args_count + 1);
	*envp = ft_realloc(*envp, old_size, new_size);
	if (!*envp)
	{
		printf("malloc failed for *envp\n");
		exit(-1);
	}
	add_valid_args(*envp, args);
}

static void	handle_export_envp(char **envp)
{
	pad_envp_entry(envp);
	radix_sort(envp);
	trim_entry_pad(envp);
	print_export_envp(envp);
}

// My export works on static to store the all args that you have used
// It also ignored empty string, so that is easier to implement unset
// Remeber to pass a static to args_history before the call
int	blt_export(char ***envp, t_subtokennode *args)
{
	insert_valid_args(envp, args);
	if (args == NULL)
		handle_export_envp(*envp);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**temp;

// 	temp = envp;
// 	envp = malloc(sizeof(char *) * (count_envp_size(envp) + 1));
// 	from_envp(envp, temp);

// 	t_subtokennode	first;
// 	t_subtokennode	second;
// 	t_subtokennode	third;
// 	t_subtokennode	fourth;
// 	t_subtokennode	fifth;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = NULL;
// 	fourth.next = &fifth;;
// 	fifth.next = NULL;

// 	first.subtoken = "hi";
// 	second.subtoken = "bye";
// 	third.subtoken = "=";
// 	fourth.subtoken = "ABC=";
// 	fifth.subtoken = "NAME=MAX";

// 	blt_export(&envp, &first);
// 	blt_export(&envp, &fourth);

// 	int	i;

// 	i = -1;
// 	while (envp[++i])
// 		printf("%s\n",envp[i]);
// 	free_envp(envp);
// }