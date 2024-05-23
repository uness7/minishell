/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:36:08 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/23 17:58:34 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exit(void)
{
	close(0);
	close(1);
	close(2);
}

static void	check_number_args(t_arena *arena, int i, int *status)
{
	(void)arena;
	if (i > 2)
	{
		printf("Too many arguments \n");
		*status = 1;
		rl_clear_history();
		close_exit();
		exit(WEXITSTATUS(*status));
	}
}

void	ft_exit(t_stock *stock, char *input, int *status)
{
	int		i;
	char	**args;
	char	*endptr;
	char	*temp;
	long	num;   

	i = 0;
	args = convert_list_array(stock->arena, tokenize(stock->arena, input));
	i = array_size(args);
	check_number_args(stock->arena, i, status);
	if (args[1] != NULL)
	{
		temp = trim_quotes(stock->arena, trim_space(args[1]));
		errno = 0;
		num = ft_strtol(temp, &endptr, 10);
		if ((*endptr != '\0' || errno != 0) || num > INT_MAX || num < INT_MIN)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			*status = 2;
		}
		else
			*status = (int)num;
	}
	free_arena(stock->arena);
	free_arena(stock->env_arena);
	rl_clear_history();
	close_exit();
	exit(*status);
}
