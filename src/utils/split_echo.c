/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:31:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/22 11:41:42 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_echo_arr	*extract_token(t_arena *arena, char *data, int type)
{
	t_echo_arr	*res;

	res = arena_alloc(arena, sizeof(t_echo_arr));
	res->data = ft_strdup(arena, data);
	res->type = type;
	return (res);
}

static void	get_len(int *i, char *input, int *flag)
{
	char	temp;

	while (input[*i] && (*flag || input[*i] != ' '))
	{
		temp = input[*i];
		if (temp == '"' || temp == '\'')
		{
			(*i)++;
			*flag = !(*flag);
			break ;
		}
		(*i)++;
	}
}

static char	*get_temp_data(t_arena *arena, char *input, int size,
		int start_index)
{
	char	*temp_data;

	temp_data = arena_alloc(arena, (size + 1) * sizeof(char));
	ft_strncpy(temp_data, input + start_index, size);
	temp_data[size] = '\0';
	return (temp_data);
}

void	get_res_helper(t_echo_state *state, t_arena *arena, t_echo_arr **res,
		int *inside_quotes)
{
	if (is_quotes(state->input[state->i]))
	{
		*inside_quotes = !(*inside_quotes);
		(state->i)++;
	}
	else if (!(*inside_quotes) && is_space(state->input[state->i]))
	{
		res[(state->k)++] = extract_token(arena, "SPACE", _SPACE);
		while (state->input[state->i] && state->input[state->i] == ' ')
			state->i++;
	}
	else
	{
		state->start_index = state->i;
		get_len(&(state->i), state->input, inside_quotes);
		if (state->start_index <= (int)ft_strlen(state->input))
		{
			res[state->k] = extract_token(arena, get_temp_data(arena,
						state->input, state->i - state->start_index,
						state->start_index), WORD);
			remove_last_quote(res[(state->k)++]->data);
		}
	}
}
