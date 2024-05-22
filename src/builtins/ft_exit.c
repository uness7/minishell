/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:36:08 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/22 21:37:33 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_number_args(t_arena *arena, int i, int *status)
{
	if (i > 2)
	{
		printf("Too many arguments \n");
		*status = 1;
		free_arena(arena);
		close_exit();
		exit(WEXITSTATUS(*status));
	}
}

static void	check_status(t_arena *arena, int *status)
{
	if (*status > MAX_INT)
	{
		printf("exit numeric argument required\n");
		*status = 2;
		free_arena(arena);
		close_exit();
		exit(*status);
	}
}

void	close_exit(void)
{
	close(0);
	close(1);
	close(2);
}

//temp = trim_space(trim_quotes(arena, args[1]));
void	ft_exit(t_arena *arena, char *input, int *status)
{
	int		i;
	char	**args;
	char	*temp;

	i = 0;
	args = convert_list_array(arena, tokenize(arena, input));
	i = array_size(args);
	check_number_args(arena, i, status);
	if (args[1] != NULL)
	{
		temp = trim_quotes(arena, trim_space(args[1]));
		if (!is_num(temp))
		{
			printf("exit : %s: numeric argument required\n", args[1]);
			*status = 2;
			free_arena(arena);
			close_exit();
			exit((*status));
		}
		*status = ft_atoi(temp);
		check_status(arena, status);
	}
	free_arena(arena);
	close_exit();
	exit(*status);
}
