/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:43:41 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 17:56:02 by yzioual          ###   ########.fr       */
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

void	copy_result(t_arena *arena, char *input, char ***result, int *count)
{
	(*result)[*count] = ft_strdup(arena, input);
	(*result)[++(*count)] = ft_strdup(arena, "\n");
}

char	**get_input_helper(t_arena *arena, int i, int count, char *eof)
{
	char	**result;
	char	*input;

	result = arena_alloc(arena, sizeof(char *) * HEREDOC_SIZE);
	while (1)
	{
		input = readline("> ");
		if (++i > 100)
			err();
		if (!input)
			break ;
		if (input && ft_strcmp(input, eof) == 0)
			break ;
		copy_result(arena, input, &result, &count);
		free(input);
	}
	return (result);
}

char	**get_input(t_arena *arena, char *eof)
{
	int		i;
	int		count;
	char	**result;

	i = -1;
	count = 0;
	result = get_input_helper(arena, i, count, eof);
	return (result);
}
