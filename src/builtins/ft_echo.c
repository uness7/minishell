/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:42:27 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/04 16:13:45 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_str_for_n_char(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	jump_spaces(t_echo_arr ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		if ((*arr)[i]->type != _SPACE)
			break ;
		(*arr)++;
		i++;
	}
}

void	echo_helper(t_echo_arr **echo_args, int *flag)
{
	int	i;

	i = 0;
	while (echo_args[i] != NULL)
	{
		if (ft_strncmp(echo_args[i]->data, "-", 1) == 0
			&& check_str_for_n_char(echo_args[i]->data))
		{
			i++;
			*flag = 1;
		}
		if (echo_args[i] && echo_args[i]->type == WORD)
			printf("%s", echo_args[i]->data);
		else if (echo_args[i] && echo_args[i - 1] && echo_args[i + 1]
			&& echo_args[i - 1]->type == WORD && echo_args[i + 1]->type == WORD
			&& echo_args[i]->type == _SPACE && \
			!(ft_strncmp(echo_args[i - 1]->data, "-", 1) == 0 \
				&& check_str_for_n_char(echo_args[i - 1]->data)))
		{
			printf(" ");
		}
		i++;
	}
}

int	ft_echo(t_arena *arena, char *input)
{
	int			flag;
	t_echo_arr	**echo_args;

	flag = 0;
	echo_args = split(arena, input);
	jump_spaces(&echo_args);
	echo_helper(echo_args, &flag);
	if (flag == 0)
		printf("\n");
	return (0);
}