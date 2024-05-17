/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:44:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/17 23:19:19 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_single_unclosed_quotes(char *s)
{
	bool	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\'')
			flag = !flag;
		s++;
	}
	return (flag);
}

bool	has_double_unclosed_quotes(char *s)
{
	bool	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\"')
			flag = !flag;
		s++;
	}
	return (flag);
}
int	heredoc_cmd(char *start_delim)
 {
	 int             nbytes;
	 int             len_start;
	 char            buff[BUFFERSIZE + 1];
	 int             fd;

	 len_start = 1;
	 fd = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	 //unlink("tmp.txt");
	 if (fd == -1)
		 return -1;
	 write(1, "heredoc> ", 9);
	 while ((nbytes = read(0, buff, BUFFERSIZE)) > 0)
	 {
		 if (g_status == 130)
			 break ;
		 if (nbytes == -1 && errno == EINTR)
			 break ;
		 buff[nbytes] = 0;
		 if (nbytes == len_start + 1 && (memcmp(start_delim, buff, len_start) == 0) && buff[nbytes - 1] == '\n') {
			 break;
		 }
		 write(1, "heredoc> ", 9);
	 }
	 return (fd);
  }
