/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:58:21 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 18:21:45 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	take_input2(char *input, size_t size)
{
	char	*newline_pos;
	ssize_t	bytes_read;

	newline_pos = NULL;
	write(1, "> ", 2);
	signal(SIGINT, handle_sig);
	bytes_read = read(STDIN_FILENO, input, size - 1);
	if (bytes_read > 0)
	{
		input[bytes_read] = '\0';
		newline_pos = ft_strchr(input, '\n');
		if (newline_pos)
			*newline_pos = '\0';
	}
	return (bytes_read);
}

void	heredoc_cmd2(t_arena *arena, char *input)
{
	char	*temp;

	temp = arena_alloc(arena, BUFFER_SIZE * sizeof(char));
	if (take_input2(temp, BUFFER_SIZE) > 0)
		append_input(input, temp, BUFFER_SIZE);
	free(temp);
}
