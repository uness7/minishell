/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:43:41 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/12 17:57:08 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(t_arena *arena, char *s)
{
	size_t		s_size;
	char		*block;
	int			i;
	const char	*temp;

	s_size = 0;
	if (s == NULL)
		return (NULL);
	temp = s;
	while (*s)
	{
		s_size++;
		s++;
	}
	block = arena_alloc(arena, s_size + 1);
	if (block == NULL)
		return (NULL);
	i = 0;
	while (temp[i] != '\0')
	{
		block[i] = temp[i];
		i++;
	}
	block[i] = '\0';
	return (block);
}
