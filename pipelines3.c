/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:41:37 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/30 13:55:02 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_r_out(t_stock *stock, t_sk_1 *sk, char *path, t_cmd *cmd)
{
	*(sk->fd_flag) = 1;
	*(sk->fd) = open(cmd->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*(sk->fd) == -1)
		open_err();
	dup2(*(sk->fd), STDOUT_FILENO);
	execve(path, cmd->av, sk->envp);
	execve_err(stock->arena, stock->env);
}

void	run_r_in(t_stock *stock, t_sk_1 *sk, char *path, t_cmd *cmd)
{
	*(sk->fd_flag) = 1;
	*(sk->fd) = open(cmd->target, O_RDONLY, 0644);
	if (*(sk->fd) == -1)
		open_err();
	dup2(*(sk->fd), STDIN_FILENO);
	execve(path, cmd->av, sk->envp);
	execve_err(stock->arena, stock->env);
}

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	exchange_fd(int fd_prev[2], int fd_curr[2])
{
	fd_prev[1] = fd_curr[1];
	fd_prev[0] = fd_curr[0];
}
