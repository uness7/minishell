/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:21:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/19 15:43:58 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_words_count(const char *s, char delim)
{
	int	i;
	int	in_word;
	int	count;

	if (s == NULL)
		return (-1);
	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] <= 32 || s[i] == delim)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**allocate_memory(t_arena *arena, int size)
{
	char	**result;

	result = arena_alloc(arena, sizeof(char *) * size);
	if (result == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	return (result);
}

static char	*allocate_memory_string(t_arena *arena, int size)
{
	char	*result;

	result = arena_alloc(arena, sizeof(char *) * size);
	if (result == NULL)
	{
		printf("Error allocating\n");
		return (NULL);
	}
	return (result);
}

char	**ft_split(t_arena *arena, const char *str, char delim)
{
	t_stock_split	s;

	if (str == NULL)
		return (NULL);
	s.words_count = ft_words_count(str, delim);
	s.result = allocate_memory(arena, s.words_count + 1);
	s.k = -1;
	s.i = 0;
	while (++s.k < s.words_count)
	{
		while (str[s.i] && (str[s.i] <= 32 || str[s.i] == delim))
			s.i++;
		s.start = s.i;
		while (str[s.i] && str[s.i] > 32 && str[s.i] != delim)
			s.i++;
		s.word_len = s.i - s.start;
		s.result[s.k] = allocate_memory_string(arena, s.word_len + 1);
		s.temp = -1;
		while (++s.temp < s.word_len)
			s.result[s.k][s.temp] = str[s.start + s.temp];
		s.result[s.k][s.temp] = '\0';
	}
	s.result[s.words_count] = NULL;
	return (s.result);
}
