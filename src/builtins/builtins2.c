/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:38:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 15:02:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}


int	count_words(char *str)
{
	int		inside_quotes;
	int		word_count;
	int		str_length;
	int		i;

	inside_quotes = 0;
	word_count = 0;
	str_length = ft_strlen(str);
	i = 0;
	while (i < str_length)
	{
		if (is_quote(str[i]))
			inside_quotes = !inside_quotes;
		else if (!inside_quotes && (is_space(str[i]) || str[i] == '\0') && (i == 0 || !is_quote(str[i - 1])))
			word_count++;
		i++;
	}
	return (word_count);
}

char	**allocate_memory(int word_count)
{
	char **result;
	
	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	return (result);
}

void	copy_word(char *dest, char *src, int start, int end)
{
	ft_strncpy(dest, src + start, end - start);
	dest[end - start] = '\0';
}

char	**split_string(char *str, int word_count)
{
	int	inside_quotes = 0;
	int	word_index = 0;
	int	start_index = 0;
	int	quoted_start = -1;
	int	str_length = strlen(str);
	int	i = 0;
	char	**result = allocate_memory(word_count);

	while (i <= str_length)
	{
		if (is_quote(str[i]))
		{
			inside_quotes = !inside_quotes;
			if (inside_quotes)
				quoted_start = i;
			else if (quoted_start != -1 && i - start_index > 1)
			{
				result[word_index] = malloc((i - start_index + 1) * sizeof(char));
				copy_word(result[word_index], str, start_index, i);
				word_index++;
				start_index = i + 1;
				quoted_start = -1;
			}
		}
		else if (!inside_quotes && (is_space(str[i]) || str[i] == '\0'))
		{
			if (i > start_index)
			{
				result[word_index] = malloc((i - start_index + 1) * sizeof(char));
				copy_word(result[word_index], str, start_index, i);
				word_index++;
			}
			start_index = i + 1;
		}
		i++;
	}
	result[word_index] = NULL;
	return result;
}

char	**ft_split_2(t_arena *arena, char *str)
{
	int	word_count;
	(void)arena;

	word_count = count_words(str);
	return (split_string(str, word_count));
}
