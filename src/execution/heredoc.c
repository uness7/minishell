/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:53:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 16:32:01 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// memcmp

static int	open_file(const char *filename)
{
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("Failed to open file");
	return (fd);
}

static int	read_until_delim(int fd, const char *delim, int delim_len)
{
	int		nbytes;
	char	buff[BUFFERSIZE + 1];

	while (1)
	{
		write(1, "heredoc> ", 9);
		nbytes = read(0, buff, BUFFERSIZE);
		if (g_status == 130 || (nbytes == -1 && errno == EINTR))
			return (-1);
		if (nbytes > 0)
		{
			buff[nbytes] = 0;
			if (nbytes == delim_len + 1 \
			&& memcmp(delim, buff, delim_len) \
			== 0 && buff[nbytes - 1] == '\n')
				return (0);
			write(fd, buff, nbytes);
		}
	}
	return (0);
}

int	heredoc(char *start_delim, char *end_delim, const char *filename)
{
	int	fd;
	int	len_start;
	int	len_end;

	if (start_delim != NULL)
		len_start = ft_strlen(start_delim);
	if (end_delim != NULL)
		len_end = ft_strlen(end_delim);
	fd = open_file(filename);
	if (start_delim != NULL && \
		read_until_delim(fd, start_delim, len_start) == -1)
	{
		close(fd);
		return (-1);
	}
	if (end_delim != NULL && read_until_delim(fd, end_delim, len_end) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("Failed to reopen file");
	return (fd);
}
