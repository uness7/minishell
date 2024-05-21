/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_echo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:45:29 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 14:32:20 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_echo_arr	**get_res(t_arena *arena, char *input, t_echo_arr **res,
		int inside_quotes)
{
	t_echo_state	state;

	state.i = 0;
	state.k = 0;
	state.input = input;
	while (state.input[state.i] != '\0')
		get_res_helper(&state, arena, res, &inside_quotes);
	res[state.k] = NULL;
	return (res);
}

t_echo_arr	**split(t_arena *arena, char *input)
{
	int			inside_quotes;
	t_echo_arr	**res;

	inside_quotes = 0;
	res = arena_alloc(arena, (ft_strlen(input)) * (sizeof(t_echo_arr *)) + 1);
	input += 5;
	return (get_res(arena, input, res, inside_quotes));
}

void	remove_last_quote(char *str)
{
	int		len;
	bool	escaped;
	int		i;

	len = ft_strlen(str);
	if (len == 0)
		return ;
	if (str[len - 1] == '"' || str[len - 1] == '\'')
	{
		escaped = false;
		i = len - 2;
		while (i >= 0 && str[i] == '\\')
		{
			escaped = !escaped;
			i--;
		}
		if (!escaped)
			str[len - 1] = '\0';
	}
}
