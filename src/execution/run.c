/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:46:42 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 17:54:49 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_cnd(char *cmd)
{
	return (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0);
}

static bool	execve_err(void)
{
	printf("Command not found\n");
	exit(127);
}

pid_t	execute_program(t_program *program, char **envp, t_pipe *pipe,
		int next_exists)
{
	char	*path;
	pid_t	pid;

	path = find_cmd(pipe->stock->arena, ft_strtok(pipe->stock->arena,
				find_paths(envp)), program->cmd);
	pid = fork();
	if (pid == 0)
	{
		if (pipe->last_fd != STDIN_FILENO)
			dup2(pipe->last_fd, STDIN_FILENO);
		if (next_exists)
		{
			close(pipe->pipefd[0]);
			dup2(pipe->pipefd[1], STDOUT_FILENO);
		}
		redirect(program);
		if (check_cnd(program->cmd))
			execve(program->cmd, program->args, envp);
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
	signal(SIGINT, handle_sig);
	process_programs(programs, envp, stock, &pipe);
	if (pipe.last_fd != STDIN_FILENO)
		close(pipe.last_fd);
	j = -1;
	while (++j < pipe.p)
		waitpid(pipe.pids[j], &status, 0);
	return (WEXITSTATUS(status));
}
