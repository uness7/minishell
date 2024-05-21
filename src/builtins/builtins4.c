/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:19:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 14:06:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}


char	**ft_split_2(t_arena *arena, char *str)
{
	(void)arena;
	int		inside_quotes;
	int		word_count;
	int		str_length;
	char	**result;
	int		word_index;
	int		start_index;
	int		quoted_start;

	inside_quotes = 0;
	word_count = 0;
	str_length = strlen(str);
	for (int i = 0; i < str_length; i++)
	{
		if (is_quote(str[i]))
		{
			inside_quotes = !inside_quotes;
		}
		else if (!inside_quotes && is_space(str[i]) && (i == 0
				|| !is_quote(str[i - 1])))
		{
			word_count++;
		}
	}
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	word_index = 0;
	start_index = 0;
	quoted_start = -1;
	for (int i = 0; i <= str_length; i++)
	{
		if (is_quote(str[i]))
		{
			inside_quotes = !inside_quotes;
			if (inside_quotes)
				quoted_start = i;
			else
			{
				if (quoted_start != -1 && i - start_index > 1)
				{
					result[word_index] = malloc((i - start_index + 1) * sizeof(char));
					strncpy(result[word_index], str + start_index, i - start_index);
					result[word_index][i - start_index] = '\0';
					word_index++;
				}
				start_index = i + 1;
				quoted_start = -1;
			}
		}
		else if (!inside_quotes && (is_space(str[i]) || str[i] == '\0'))
		{
			if (i > start_index)
			{
				result[word_index] = malloc((i - start_index + 1) * sizeof(char));
				strncpy(result[word_index], str + start_index, i - start_index);
				result[word_index][i - start_index] = '\0';
				word_index++;
			}
			start_index = i + 1;
		}
	}
	result[word_index] = NULL;
	return (result);
}
/*
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

	state.arena = arena;
	state.inside_quotes = 0;
	state.word_index = 0;
	state.start_index = 0;
	state.quoted_start = -1;
	state.str_length = ft_strlen(str);
	state.i = -1;
	state.word_count = count_words(str);
	state.result = malloc((state.word_count + 1) * sizeof(char *));
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
				state->result[state->word_index] = arena_alloc(state->arena, (state->i - state->start_index + 1) * sizeof(char));
				copy_word(state->result[state->word_index], str, state->start_index, state->i);
				state->word_index++;
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
*/
