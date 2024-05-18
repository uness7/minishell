/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:38:13 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 13:56:08 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strndup(t_arena *arena, const char *str, size_t n)
{
	size_t		length;
	size_t		i;
	char		*duplicate;
	const char	*ptr;

	ptr = str;
	length = 0;
	while (*ptr && length < n)
	{
		length++;
		ptr++;
	}
	duplicate = arena_alloc(arena, length + 1);
	i = 0;
	while (i < length)
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[length] = '\0';
	return (duplicate);
}

char	*trim_single_quotes(t_arena *arena, char *str)
{
	size_t	len;
	char	*trimmed;

	len = ft_strlen(str);
	if (len < 2 || (str[0] != '\'' && str[len - 1] != '\''))
	{
		return (ft_strdup(arena, str));
	}
	if ((str[0] == '\'' && str[len - 1] == '\''))
	{
		trimmed = arena_alloc(arena, (len - 1) * sizeof(char));
		ft_strncpy(trimmed, str + 1, len - 2);
		trimmed[len - 2] = '\0';
		return (trimmed);
	}
	return (ft_strdup(arena, str));
}
