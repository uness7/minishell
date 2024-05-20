/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:58:21 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 13:05:04 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	take_input2(char *input, size_t size)
{
	char	*newline_pos;
	ssize_t	bytes_read;

	newline_pos = NULL;
	write(1, "> ", 2);
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

void	heredoc_cmd2(char *input)
{
	char	*temp;

	temp = malloc(BUFFER_SIZE * sizeof(char));
	if (temp == NULL)
		return ;
	if (take_input2(temp, BUFFER_SIZE) > 0)
		append_input(input, temp, BUFFER_SIZE);
	free(temp);
}

void	heredoc_cmd(char *input, const char *delim)
{
	ssize_t	bytes_read;
	char	*temp;

	temp = malloc(BUFFER_SIZE * sizeof(char));
	if (temp == NULL)
		return ;
	temp[0] = '\0';
	while (1)
	{
		bytes_read = take_input(temp, BUFFER_SIZE, delim);
		if (bytes_read <= 0)
			break ;
		append_input(input, temp, BUFFER_SIZE);
		temp[0] = '\0';
	}
	free(temp);
}

ssize_t	take_input(char *input, size_t size, const char *delim)
{
	char	*newline_pos;
	ssize_t	bytes_read;
	size_t	input_len;

	input_len = strlen(input);
	newline_pos = NULL;
	write(1, "> ", 2);
	while ((bytes_read = read(STDIN_FILENO, input + input_len, size - input_len
				- 1)) > 0)
	{
		if (g_status == 130)
			break ;
		if (bytes_read == -1 && errno == EINTR)
			break ;
		if (bytes_read > 0)
		{
			input[input_len + bytes_read] = '\0';
			newline_pos = strchr(input + input_len, '\n');
			if (newline_pos)
				*newline_pos = '\0';
			if (strcmp(input + input_len, delim) == 0)
			{
				input[input_len] = '\0';
				return (-1);
			}
			input_len += bytes_read;
		}
		write(1, "> ", 2);
	}
	return (bytes_read);
}
