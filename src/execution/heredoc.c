/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:53:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 13:11:24 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_first_part(char buff[], int len_start, char *start_delim)
{
	int	nbytes;

	signal(SIGINT, handle_sig);
	write(1, "heredoc> ", 9);
	if (g_status == 130)
		return -1;
	nbytes = read(0, buff, BUFFERSIZE);
	while (nbytes > 0)
	{
		if (g_status == 130)
			return -1;
		if (nbytes == -1 && errno == EINTR)
			return -1;
		buff[nbytes] = 0;
		if (start_delim[0] == '\0' || (nbytes == len_start + 1 && (ft_memcmp(start_delim, buff,
					len_start) == 0) && buff[nbytes - 1] == '\n'))
		{
			break ;
		}
		write(1, "heredoc> ", 9);
		nbytes = read(0, buff, BUFFERSIZE);
		if (g_status == 130)
			return -1;
	}
	return 0;
}

static int	read_second_part(char buff[], int len_end, int fd, char *end_delim)
{
	int	nbytes;

	signal(SIGINT, handle_sig);
	write(1, "heredoc> ", 9);
	if (g_status == 130)
		return -1;
	nbytes = read(0, buff, BUFFERSIZE);
	while (nbytes > 0)
	{
		if (g_status == 130)
			return -1;
		if (nbytes == -1 && errno == EINTR)
			return -1;
		buff[nbytes] = 0;
		if ((end_delim[0] == '\0') || (nbytes == len_end + 1 && (ft_memcmp(end_delim, buff, len_end) == 0)
			&& buff[nbytes - 1] == '\n'))
		{
			break ;
		}
		write(fd, buff, nbytes);
		write(1, "heredoc> ", 9);
		nbytes = read(0, buff, BUFFERSIZE);
		if (g_status == 130)
			return -1;
	}
	return 0;
}

static int	open_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	heredoc(char *start_delim, char *end_delim, const char *filename)
{
	int		len_start;
	int		len_end;
	char	buff[BUFFERSIZE + 1];
	int		fd;
	int	stat = 0;

	if (start_delim != NULL)
		len_start = ft_strlen(start_delim);
	if (end_delim != NULL)
		len_end = ft_strlen(end_delim);
	fd = open_fd(filename);
	if (start_delim != NULL)
		stat = read_first_part(buff, len_start, start_delim);
	if (end_delim != NULL)
		stat = read_second_part(buff, len_end, fd, end_delim);
	close(fd);
	if (stat == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	return (fd);
}
