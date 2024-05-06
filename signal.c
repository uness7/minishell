/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:17:48 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/06 15:50:38 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		printf("Quit (core dumped)\n");
		rl_on_new_line();
	}
}

void	handle_sig2(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		printf("Quit (core dumped)\n");
		rl_on_new_line();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}
