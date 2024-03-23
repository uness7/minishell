/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:24:53 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/06 11:35:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*result;

	i = 0;
	result = malloc(n + 1);
	if (result)
	{
		while (i < n)
		{
			result[i] = s[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}

static int	ft_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static int	ft_count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**ft_free_array(char **array, int index)
{
	while (index > 0)
	{
		free(array[--index]);
	}
	free(array);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		i;
	int		count_words;

	count_words = ft_count_words(s, c);
	i = 0;
	result = (char **)malloc((count_words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			result[i] = ft_strndup(s, ft_word_len(s, c));
			if (result[i] == NULL)
				return (ft_free_array(result, i));
			i++;
			s += ft_word_len(s, c);
		}
	}
	result[i] = NULL;
	return (result);
}
