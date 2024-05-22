/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:35:52 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/22 13:35:53 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
}

void	init_heredoc_handler(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = heredoc_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
}
