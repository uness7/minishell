/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 23:07:02 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_err(void)
{
	perror("pipe ");
	exit(EXIT_FAILURE);
}

void	fork_err(void)
{
	perror("fork ");
	exit(EXIT_FAILURE);
}

void	execve_err(t_arena *arena, t_env *env)
{
	printf("Command Not Found\n");
	add_or_update_env(arena, &env, "?", ft_itoa(arena, 127));
	exit(127);
}

void	err(void)
{
	printf("You surpassed 100 input that we allowd :(\n");
	exit(0);
}
