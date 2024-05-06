/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:11:16 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 15:46:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (src == NULL)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
		dest[i] = '\0';
	return (dest);
}

char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
	char	*n;

	h = haystack;
	n = needle;
	if (*needle == '\0' || *haystack == '\0'
		|| ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (*haystack != '\0')
	{
		while (*h != '\0' && *n != '\0' && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*trim_quotes(t_arena *arena, char *str)
{
	size_t	len;
	char	*trimmed;

	len = ft_strlen(str);
	if (len < 2 || (str[0] != '"' && str[len - 1] != '"'))
	{
		return (ft_strdup(arena, str));
	}
	if ((str[0] == '"' && str[len - 1] == '"'))
	{
		trimmed = arena_alloc(arena, (len - 1) * sizeof(char));
		if (trimmed == NULL)
		{
			printf("Memory allocation failed\n");
			return (NULL);
		}
		ft_strncpy(trimmed, str + 1, len - 2);
		trimmed[len - 2] = '\0';
		return (trimmed);
	}
	return (ft_strdup(arena, str));
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'\
			|| c == '\f' || c == '\r')
		return (1);
	return (0);
}
