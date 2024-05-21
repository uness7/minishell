/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:17:48 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/21 10:44:11 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void	handle_sig2(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	g_status = 130;
}

void	handle_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	g_status = 131;
}

void	init_signal(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sig;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
}
