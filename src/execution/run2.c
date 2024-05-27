/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:37:54 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/28 00:28:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redir_out_or_app(int type)
{
	return (type == NODE_REDIRECTION_OUT || type == NODE_REDIRECTION_APPEND);
}

void	redirect(t_program *program)
{
	if (program->type == NODE_REDIRECTION_IN)
	{
		if (program->fd_out != 1)
		{
			dup2(program->fd_out, STDOUT_FILENO);
			close(program->fd_out);
		}
		dup2(program->fd_in, STDIN_FILENO);
		close(program->fd_in);
	}
	else if (is_redir_out_or_app(program->type))
	{
		dup2(program->fd_out, STDOUT_FILENO);
		close(program->fd_out);
	}
	else if (program->type == NODE_REDIRECTION_HEREDOC)
	{
		if (program->fd_out != 1)
		{
			dup2(program->fd_out, STDOUT_FILENO);
			close(program->fd_out);
		}
		dup2(program->fd_in, STDIN_FILENO);
		close(program->fd_in);
	}
}

static t_program_state	*init(t_program_state *state, t_program *curr,
		t_program *prev, t_program *next)
{
	state = arena_alloc(state->stock->arena, sizeof(t_program_state *));
	state->curr = curr;
	state->prev = prev;
	state->next = next;
	return (state);
}

static void	_redir(t_pipe *pipe_data, int next_exists)
{
	if (pipe_data->last_fd != STDIN_FILENO)
		close(pipe_data->last_fd);
	if (next_exists)
	{
		close(pipe_data->pipefd[1]);
		pipe_data->last_fd = pipe_data->pipefd[0];
	}
}

void	process_programs(t_program **programs, char **envp, \
		t_stock *stock, t_pipe *pipe_data)
{
	int				next_exists;
	int				i;
	t_program_state	state;

	state.stock = stock;
	pipe_data->path = NULL;
	pipe_data->new_input = NULL;
	stock->last_status = 0;
	i = 0;
	while (programs[i])
	{
		if (programs[i] == NULL)
			i++;
		else
		{
			next_exists = programs[i + 1] != NULL;
			if (next_exists && pipe(pipe_data->pipefd) == -1)
				pipe_err();
			if (i == 0 && !next_exists && _isbuiltin(stock->arena, \
						programs[i]->cmd))
				stock->last_status = handle_builtin(init(&state, \
							programs[i], programs[i - 1], programs[i + 1]), stock, i);
			else
				pipe_data->pids[pipe_data->p++] = execute_program(programs[i], \
						envp, pipe_data, next_exists);
			_redir(pipe_data, next_exists);
		}
		i++;
	}
}
