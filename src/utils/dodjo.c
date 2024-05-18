/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dodjo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:37:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 18:03:05 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arena_init(t_arena *arena, size_t capacity)
{
	arena->buffer = malloc(capacity);
	if (!arena->buffer)
	{
		printf("Error Allocating Arena\n");
		return ;
	}
	arena->offset = 0;
	arena->capacity = capacity;
}

void	free_arena(t_arena *arena)
{
	free(arena->buffer);
	arena->buffer = NULL;
	arena->offset = 0;
	arena->capacity = 0;
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->offset + size > arena->capacity)
		return (NULL);
	ptr = arena->buffer + arena->offset;
	arena->offset += size;
	return (ptr);
}
