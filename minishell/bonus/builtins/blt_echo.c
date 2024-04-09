/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:02:22 by ychng             #+#    #+#             */
/*   Updated: 2024/04/10 01:47:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static void	print_subtokens(t_subtokennode *args)
{
	args = find_first_non_option(args);
	while (args)
	{
		printf("%s", args->subtoken);
		if (args->next != NULL)
			printf(" ");
		args = args->next;
	}
}

static void	print_newline(t_subtokennode *args)
{
	t_subtokennode	*first_non_option;

	first_non_option = find_first_non_option(args);
	if (first_non_option == args)
		printf("\n");
}

int	blt_echo(t_subtokennode *args)
{
	if (args == NULL)
	{
		printf("\n");
		return (0);
	}
	print_subtokens(args);
	print_newline(args);
	return (0);
}

// int main()
// {
// 	t_subtokennode	first;
// 	t_subtokennode	second;
// 	t_subtokennode	third;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = NULL;

// 	first.subtoken = "-nnnnnnnnnnnn";
// 	second.subtoken = "-nnnm";
// 	third.subtoken = "so what";
// 	blt_echo(&first);
// }