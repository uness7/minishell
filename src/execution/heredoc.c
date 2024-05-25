/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:53:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 18:51:46 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	init_terminal_settings(struct termios *old_termios)
{
	struct termios	new_termios;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, old_termios) == -1)
		{
			perror("tcgetattr");
			exit(EXIT_FAILURE);
		}
		new_termios = *old_termios;
		new_termios.c_lflag &= ~(ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
		{
			perror("tcsetattr");
			exit(EXIT_FAILURE);
		}
	}
}

void	restore_terminal_settings(const struct termios *old_termios)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, old_termios) == -1)
		{
			perror("tcsetattr");
			exit(EXIT_FAILURE);
		}
	}
}

int	heredoc(char *start_delim, char *end_delim, char *filename, struct termios *old_termios)
{
	int				len_start;
	int				len_end;
	char			buff[BUFFERSIZE + 1];
	int				fd;
	int				stat;

	init_terminal_settings(&old_termios);
	stat = 0;
	init_heredoc_handler();
	if (start_delim != NULL)
		len_start = ft_strlen(start_delim);
	if (end_delim != NULL)
		len_end = ft_strlen(end_delim);
	fd = open_fd(filename);
	if (start_delim != NULL)
		stat = read_first_part(buff, len_start, start_delim);
	if (end_delim != NULL && stat != -1)
		stat = read_second_part(buff, len_end, fd, end_delim);
	close(fd);
	restore_terminal_settings(&old_termios);
	if (stat == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	return (fd);
}
