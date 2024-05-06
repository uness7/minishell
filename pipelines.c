/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:53:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 19:13:26 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dispenser(t_cmd *cmd, char *path, int fd_curr[2], t_sk_1 *sk)
{
	if (cmd->type == R_OUT)
		run_r_out(sk->stock, sk, path, cmd);
	else if (cmd->type == R_IN)
		run_r_in(sk->stock, sk, path, cmd);
	else if (cmd->type == R_APPEND)
	{
		*(sk->fd_flag) = 1;
		*(sk->fd) = open(cmd->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*(sk->fd) == -1)
			open_err();
		dup2(*(sk->fd), STDOUT_FILENO);
		execve(path, cmd->av, sk->envp);
		execve_err(sk->stock->arena, sk->stock->env);
	}
	else if (cmd->type == R_HEREDOC)
		_execute_redir_heredoc(sk->stock, fd_curr, cmd);
	else if (cmd->type == SIMPLE)
	{
		execve(path, cmd->av, sk->envp);
		execve_err(sk->stock->arena, sk->stock->env);
	}
	close(*(sk->fd_flag));
}

static void	run_child(int *i, int fd_prev[2], int fd_curr[2], t_sk_1 *sk)
{
	char	*path;

	if (ft_strncmp(sk->cmds[*i]->av[0], "/", 1) == 0)
		path = sk->cmds[*i]->av[0];
	else
	{
		path = find_cmd(sk->stock->arena, ft_strtok(sk->stock->arena,
					find_paths(env_list_arr(sk->stock->arena, sk->stock->env,
							env_list_size(sk->stock->env)))),
				sk->cmds[*i]->av[0]);
	}
	if (*i > 0)
	{
		dup2(fd_prev[0], STDIN_FILENO);
		close_fd(fd_prev);
	}
	if (*i < sk->num_cmds - 1)
	{
		if (sk->cmds[*i]->type != R_HEREDOC)
		{
			dup2(fd_curr[1], STDOUT_FILENO);
			close_fd(fd_curr);
		}
	}
	dispenser(sk->cmds[*i], path, fd_curr, sk);
}

static void	loop_while(t_sk_1 *sk1, int fd_curr[2], int fd_prev[2])
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < sk1->num_cmds)
	{
		if (i < sk1->num_cmds - 1)
			if (pipe(fd_curr) == -1)
				pipe_err();
		signal(SIGINT, handle_sig2);
		pid = fork();
		if (pid == 0)
			run_child(&i, fd_prev, fd_curr, sk1);
		else if (pid < 0)
			fork_err();
		else
		{
			if (i > 0)
				close_fd(fd_prev);
			if (i < sk1->num_cmds - 1)
				exchange_fd(fd_prev, fd_curr);
		}
		i++;
	}
}

static void	set_sk(t_sk_1 *sk_1, t_cmd **cmds, int fd_flag, int fd)
{
	sk_1->fd = &fd;
	sk_1->fd_flag = &fd_flag;
	sk_1->cmds = cmds;
	sk_1->num_cmds = 0;
}

int	execute_pipeline(t_stock *stock, t_cmd **cmds, int *i, int *fd)
{
	int		status;
	int		fd_prev[2];
	int		fd_curr[2];
	t_sk_1	sk_1;
	int		fd_flag;

	status = 0;
	fd_flag = 0;
	set_sk(&sk_1, cmds, fd_flag, *fd);
	sk_1.envp = stock->envp;
	sk_1.stock = stock;
	while (cmds[sk_1.num_cmds])
		(sk_1.num_cmds)++;
	loop_while(&sk_1, fd_curr, fd_prev);
	if (*(sk_1.fd_flag) == 1)
		close(*(sk_1.fd));
	if (sk_1.num_cmds > 1)
	{
		close(fd_curr[0]);
		close(fd_curr[1]);
	}
	*i = -1;
	while (++(*i) < sk_1.num_cmds)
		wait(&status);
	return (WEXITSTATUS(status));
}
