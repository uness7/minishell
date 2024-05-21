/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:11:16 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 12:07:51 by yzioual          ###   ########.fr       */
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

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
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
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r');
}
