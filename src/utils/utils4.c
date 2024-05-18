/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:11:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 22:52:58 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

char	*ft_strchr(char *str, int c)
{
	unsigned char	target;
	const char		*ptr;

	target = (unsigned char)c;
	ptr = str;
	while (*ptr != '\0')
	{
		if (*ptr == target)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == target)
		return ((char *)ptr);
	return (NULL);
}
