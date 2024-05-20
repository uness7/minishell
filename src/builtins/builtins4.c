/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:19:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 17:19:15 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	**allocate_memory(int word_count)
{
	char	**result;

	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	return (result);
}

int	count_words(char *str)
{
	int	inside_quotes;
	int	word_count;
	int	str_length;
	int	i;

	inside_quotes = 0;
	word_count = 0;
	str_length = ft_strlen(str);
	i = 0;
	while (i < str_length)
	{
		if (is_quote(str[i]))
			inside_quotes = !inside_quotes;
		else if (!inside_quotes && (is_space(str[i]) || str[i] == '\0')
			&& (i == 0 || !is_quote(str[i - 1])))
			word_count++;
		i++;
	}
	return (word_count);
}

char	**ft_split_2(t_arena *arena, char *str)
{
	t_split_2_state	state;

	(void)arena;
	state.inside_quotes = 0;
	state.word_index = 0;
	state.start_index = 0;
	state.quoted_start = -1;
	state.str_length = strlen(str);
	state.i = -1;
	state.word_count = count_words(str);
	state.result = allocate_memory(state.word_count);
	state.result = split_string(str, &state);
	state.result[state.word_index] = NULL;
	return (state.result);
}

char	**split_string(char *str, t_split_2_state *state)
{
	while (++state->i <= state->str_length)
	{
		if (is_quote(str[state->i]))
		{
			state->inside_quotes = !state->inside_quotes;
			if (state->inside_quotes)
				state->quoted_start = state->i;
			else if (state->quoted_start != -1 && state->i
				- state->start_index > 1)
			{
				state->result[state->word_index] = malloc((state->i
							- state->start_index + 1) * sizeof(char));
				copy_word(state->result[(state->word_index)++], str,
					state->start_index, state->i);
				state->start_index = state->i + 1;
				state->quoted_start = -1;
			}
		}
		else if (!state->inside_quotes && (is_space(str[state->i])
				|| str[state->i] == '\0'))
			split_string_helper(state, str);
	}
	return (state->result);
}
