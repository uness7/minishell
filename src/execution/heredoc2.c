/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:01 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 17:33:13 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sigint_code(void)
{
	if (g_status == 130)
	{
		printf("\n");
		return (-1);
	}
	return (0);
}

int	read_first_part(char buff[], int len_start, char *start_delim)
{
	int	nbytes;

	write(1, "heredoc> ", 9);
	nbytes = read(0, buff, BUFFERSIZE);
	if (check_sigint_code() == -1)
		return (-1);
	while (nbytes > 0)
	{
		if (check_sigint_code() == -1)
			return (-1);
		if (nbytes == -1 && errno == EINTR)
			return (-1);
		buff[nbytes] = 0;
		if (start_delim[0] == '\0' || (nbytes == len_start + 1
				&& (ft_memcmp(start_delim, buff, len_start) == 0) && buff[nbytes
					- 1] == '\n'))
			break ;
		write(1, "heredoc> ", 9);
		nbytes = read(0, buff, BUFFERSIZE);
		if (check_sigint_code() == -1)
			return (-1);
	}
	return (0);
}

int	read_second_part(char buff[], int len_end, int fd, char *end_delim)
{
	int	nbytes;

	write(1, "heredoc> ", 9);
	nbytes = read(0, buff, BUFFERSIZE);
	if (check_sigint_code() == -1)
		return (-1);
	while (nbytes > 0)
	{
		if (check_sigint_code() == -1)
			return (-1);
		if (nbytes == -1 && errno == EINTR)
			return (-1);
		buff[nbytes] = 0;
		if ((end_delim[0] == '\0') || (nbytes == len_end + 1
				&& (ft_memcmp(end_delim, buff, len_end) == 0) && buff[nbytes
					- 1] == '\n'))
			break ;
		write(fd, buff, nbytes);
		write(1, "heredoc> ", 9);
		nbytes = read(0, buff, BUFFERSIZE);
		if (check_sigint_code() == -1)
			return (-1);
	}
	return (0);
}
