/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:46:42 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/27 23:36:34 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_cnd(char *cmd)
{
	return (ft_strncmp(cmd, ".", 1) == 0 || ft_strncmp(cmd, "/", 1) == 0);
}

static bool	execve_err(void)
{
	ft_putstr_fd(" command not found\n", 2);
	exit(127);
}

static void	run_child(t_pipe *pipe, int next_exists)
{
	if (pipe->last_fd != STDIN_FILENO)
	{
		dup2(pipe->last_fd, STDIN_FILENO);
		close(pipe->last_fd);
	}
	if (next_exists)
	{
		close(pipe->pipefd[0]);
		dup2(pipe->pipefd[1], STDOUT_FILENO);
		close(pipe->pipefd[1]);
	}
}

pid_t	execute_program(t_program *program, char **envp, t_pipe *pipe,
		int next_exists)
{
	char	*path;
	pid_t	pid;

	path = find_cmd(pipe->stock->arena, ft_strtok(pipe->stock->arena, \
			find_paths(envp)), program->cmd);
	pid = fork();
	if (pid == 0)
	{
		run_child(pipe, next_exists);
		redirect(program);
		if (_isbuiltin(pipe->stock->arena, program->cmd))
		{
			pipe->new_input = join_args(pipe->stock->arena, program->args);
			exit(_runbuiltins(pipe->stock, pipe->new_input));
		}
		else if (check_cnd(program->cmd))
		{
			if (ft_strncmp(program->cmd, ".", 1) == 0)
			{
				execve(change_path_run(pipe->stock, \
							program->cmd), program->args, envp);
			}
			else
				execve(program->cmd, program->args, envp);
		}
		else
			execve(path, program->args, envp);
		execve_err();
	}
	else if (pid < 0)
		fork_err();
	return (pid);
}

int	run_programs(t_program **programs, char **envp, t_stock *stock)
{
	int		status;
	int		j;
	t_pipe	pipe;

	pipe.stock = stock;
	status = 0;
	pipe.p = 0;
	pipe.last_fd = STDIN_FILENO;
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_sig2);
	process_programs(programs, envp, stock, &pipe);
	if (pipe.last_fd != STDIN_FILENO)
		close(pipe.last_fd);
	close_fds(pipe.stock);
	j = -1;
	while (++j < pipe.p)
		waitpid(pipe.pids[j], &status, 0);
	if (pipe.p == 0)
		return (pipe.stock->last_status);
	return (WEXITSTATUS(status));
}
