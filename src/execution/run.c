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

static void run_builtin(t_program *program, t_program *prev_program)
{
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stderr = dup(STDERR_FILENO);

	if (program->fd_out != STDOUT_FILENO) {
		dup2(program->fd_out, STDOUT_FILENO);
		close(program->fd_out);
	}
	if (program->fd_in != STDIN_FILENO) {
		dup2(program->fd_in, STDIN_FILENO);
		close(program->fd_in);
	}
	if (prev_program && ft_strcmp(program->cmd, "echo") == 0) {
		char *new_input = join_args(stock->arena, program->args);
		_runbuiltins(stock, new_input);
	} else if ((i == 0 && ft_strcmp(program->cmd, "echo") != 0) ||
			(!programs[i + 1] && (ft_strcmp(program->cmd, "echo") == 0 || ft_strcmp(program->cmd, "pwd") == 0))) {
		char *new_input = join_args(stock->arena, program->args);
		_runbuiltins(stock, new_input);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stderr);
}

static void	redirection(int i, t_program **programs, int last_fd, int pipefd[2])
{
    if (i > 0)
	    dup2(last_fd, STDIN_FILENO);
    if (programs[i + 1])
    {
	    close(pipefd[0]);
	    dup2(pipefd[1], STDOUT_FILENO);
    }
    if (programs[i]->type == NODE_REDIRECTION_IN)
    {
	    if (programs[i]->fd_out != 1)
	    {
		    dup2(programs[i]->fd_out, STDOUT_FILENO);
		    close(programs[i]->fd_out);
	    }
	    dup2(programs[i]->fd_in, STDIN_FILENO);
	    close(programs[i]->fd_in);
    }
    else if (programs[i]->type == NODE_REDIRECTION_OUT || programs[i]->type == NODE_REDIRECTION_APPEND)
    {
	    dup2(programs[i]->fd_out, STDOUT_FILENO);
	    close(programs[i]->fd_out);
    }
    else if (programs[i]->type == NODE_REDIRECTION_HEREDOC)
    {
	    if (programs[i]->fd_out != 1)
	    {
		    dup2(programs[i]->fd_out, STDOUT_FILENO);
		    close(programs[i]->fd_out);
	    }
	    dup2(programs[i]->fd_in, STDIN_FILENO);
	    close(programs[i]->fd_in);
    }
}

static void	run_child(t_stock *stock, char **envp, t_program *program, int last_fd, int i)
{
	char *path = find_cmd(stock->arena, ft_strtok(stock->arena, find_paths(envp)), programs[i]->cmd);
	pid_t pid = fork();

	if (pid == 0)
	{
		if (strncmp(program->cmd, "./", 2) == 0 || strncmp(program->cmd, "/", 1) == 0)
			execve(program->cmd, program->args, envp);
		else
			execve(path, program->args, envp);
		printf("Command Not Found\n");
		exit(127);
	}
	else if (pid < 0)
		fork_err();
	else
		pids[p++] = pid;
}

int	run_programs(t_program **programs, char **envp, t_stock *stock, char *input)
{
	int i = 0;
	int pipefd[2];
	int last_fd = STDIN_FILENO;
	pid_t pids[256];
	int p = 0;

	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_sig);

	while (programs[i]) {
		int next_exists = programs[i + 1] != NULL;
		if (next_exists && pipe(pipefd) == -1) {
			perror("Pipe syscall failed: ");
			exit(EXIT_FAILURE);
		}
		if (_isbuiltin(stock->arena, programs[i]->cmd)) {
			run_builtin(programs[i], (i > 0) ? programs[i - 1] : NULL);
		} else {
			redirection(i, programs, last_fd, pipefd);
			run_child(stock, envp, programs[i], last_fd, i);
		}
		if (i > 0) {
			close(last_fd);
		}
		if (programs[i + 1]) {
			close(pipefd[1]);
			last_fd = pipefd[0];
		}
		i++;
	}
	if (last_fd != STDIN_FILENO) {
		close(last_fd);
	}
	int status = 0;
	for (int j = 0; j < p; j++) {
		waitpid(pids[j], &status, 0);
	}
	return WEXITSTATUS(status);
}

/*
static void	run_builtin(t_program *program, t_program *prev_program)
{
	int		saved_stdout;
	int		saved_stderr;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	if (programs[i]->fd_out != STDOUT_FILENO) {
		dup2(programs[i]->fd_out, STDOUT_FILENO);
		close(programs[i]->fd_out);
	}
	if (programs[i]->fd_in != STDIN_FILENO)
	{
		dup2(programs[i]->fd_in, STDOUT_FILENO);
		close(programs[i]->fd_in);
	}
	if (programs[i - 1] && programs[i + 1] && ft_strcmp(programs[i]->cmd, "echo") == 0 && i != 0)
	{
		char	*new_input = join_args(stock->arena, programs[i]->args);
		_runbuiltins(stock, new_input);
	}
	else if ((i == 0 && ft_strcmp(programs[i]->cmd, "echo") != 0) || (!programs[i + 1] && (ft_strcmp(programs[i]->cmd, "echo") == 0 \
					|| ft_strcmp(programs[i]->cmd, "pwd") == 0)))
	{
		char	*new_input = join_args(stock->arena, programs[i]->args);
		_runbuiltins(stock, new_input);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stderr);
}


static void	redirection()
{
	if (i > 0)
		dup2(last_fd, STDIN_FILENO);
	if (programs[i + 1])
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	if (programs[i]->type == NODE_REDIRECTION_IN)
	{
		if (programs[i]->fd_out != 1)
		{
			dup2(programs[i]->fd_out, STDOUT_FILENO);
			close(programs[i]->fd_out);
		}
		dup2(programs[i]->fd_in, STDIN_FILENO);
		close(programs[i]->fd_in);
	}
	else if (programs[i]->type == NODE_REDIRECTION_OUT ||
			programs[i]->type == NODE_REDIRECTION_APPEND)
	{
		dup2(programs[i]->fd_out, STDOUT_FILENO);
		close(programs[i]->fd_out);
	}
	else if (programs[i]->type == NODE_REDIRECTION_HEREDOC)
	{
		if (programs[i]->fd_out != 1)
		{
			dup2(programs[i]->fd_out, STDOUT_FILENO);
			close(programs[i]->fd_out);
		}
		dup2(programs[i]->fd_in, STDIN_FILENO);
		close(programs[i]->fd_in);
	}
}

static void	run_child(t_stock *stock, char **envp, t_program *program, int last_fd)
{
	char	*path;
	pid_t	pid;

	path = find_cmd(stock->arena, ft_strtok(stock->arena, find_paths(envp)), programs[i]->cmd);
	pid = fork();
	if (pid == 0)
	{
		if (strncmp(programs[i]->cmd, "./", 2) == 0 || strncmp(programs[i]->cmd, "/", 1) == 0)
			execve(programs[i]->cmd, programs[i]->args, envp);
		else
			execve(path, programs[i]->args, envp);
		printf("Command Not Found\n");
		exit(127);
	}
	else if (pid < 0)
		fork_err();
	else
		pids[p++] = pid;
}

int	run_programs(t_program **programs, char **envp, t_stock *stock, char *input)
{
	int		i;
	int		pipefd[2];
	int		last_fd;
	int		next_exists;
	pid_t 	pids[256];

	i = 0;
	last_fd = STDIN_FILENO;
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_sig);
	while (programs[i])
	{
		next_exists = programs[i + 1] != NULL;
		if (next_exists && pipe(pipefd) == -1)
		{
			perror("Pipe syscall failed: ");
			exit(EXIT_FAILURE);
		}
		if (_isbuiltin(stock->arena, programs[i]->cmd))
			run_isbuiltin(programs[i - 1], programs[i], );
		else
			run_program();
		if (i > 0)
			close(last_fd);
		if (programs[i + 1])
		{
			close(pipefd[1]);
			last_fd = pipefd[0];
		}
		i++;
	}
	if (last_fd != STDIN_FILENO)
		close(last_fd);
	int	status = 0;
	int	j = -1;
	while (++j < p)
		waitpid(pids[j], &status, 0);
	return (WEXITSTATUS(status));
}

*/
