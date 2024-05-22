/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:19:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/22 11:41:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_word_count(char *str)
{
	int	inside_quotes;
	int	str_len;
	int	i;
	int	word_count;

	i = 0;
	inside_quotes = 0;
	str_len = ft_strlen(str);
	word_count = 0;
	while (i < str_len)
	{
		if (is_quotes(str[i]))
			inside_quotes = !inside_quotes;
		else if (!inside_quotes && is_space(str[i]) && (i == 0
				|| !is_quotes(str[i - 1])))
			word_count++;
		i++;
	}
	return (word_count);
}

void	action1(t_state *state, char *str)
{
	if (state->quoted_start != -1 && state->i - state->start_index > 1)
	{
		state->result[state->word_index] = malloc((state->i - state->start_index
					+ 1) * sizeof(char));
		if (state->result[state->word_index] != NULL)
		{
			ft_strncpy(state->result[state->word_index], str
				+ state->start_index, state->i - state->start_index);
			state->result[state->word_index][state->i
				- state->start_index] = '\0';
			state->word_index++;
		}
	}
	state->start_index = state->i + 1;
	state->quoted_start = -1;
}

void	action2(t_state *state, char *str)
{
	if (state->i > state->start_index)
	{
		state->result[state->word_index] = malloc((state->i - state->start_index
					+ 1) * sizeof(char));
		if (state->result[state->word_index] != NULL)
		{
			ft_strncpy(state->result[state->word_index], str
				+ state->start_index, state->i - state->start_index);
			state->result[state->word_index][state->i
				- state->start_index] = '\0';
			state->word_index++;
		}
	}
	state->start_index = state->i + 1;
}

static void	init(t_state *state, char *str)
{
	state->inside_quotes = 0;
	state->str_length = ft_strlen(str);
	state->word_count = ft_word_count(str);
	state->result = malloc((state->word_count + 1) * sizeof(char *));
	if (state->result == NULL)
	{
		printf("Malloc failed\n");
		return ;
	}
	state->word_index = 0;
	state->start_index = 0;
	state->quoted_start = -1;
	state->i = -1;
}

char	**ft_split_2(char *str)
{
	t_state	state;

	init(&state, str);
	while (++state.i <= state.str_length)
	{
		if (is_quotes(str[state.i]))
		{
			state.inside_quotes = !state.inside_quotes;
			if (state.inside_quotes)
				state.quoted_start = state.i;
			else
				action1(&state, str);
		}
		else if (!state.inside_quotes && (is_space(str[state.i])
				|| str[state.i] == '\0'))
			action2(&state, str);
	}
	state.result[state.word_index] = NULL;
	return (state.result);
}
