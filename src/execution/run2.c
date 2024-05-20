/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:37:54 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 13:37:55 by yzioual          ###   ########.fr       */
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
	state = malloc(sizeof(t_program_state *));
	if (state == NULL)
	{
		printf("Malloc Failed\n");
		return (NULL);
	}
	state->curr = curr;
	state->prev = prev;
	state->next = next;
	return (state);
}

void	process_programs(t_program **programs, char **envp, t_stock *stock,
		t_pipe *pipe_data)

{
	int				next_exists;
	int				i;
	t_program_state	state;

	i = -1;
	while (programs[++i])
	{
		next_exists = programs[i + 1] != NULL;
		if (next_exists && pipe(pipe_data->pipefd) == -1)
			pipe_err();
		if (_isbuiltin(stock->arena, programs[i]->cmd))
			handle_builtin(init(&state, programs[i], programs[i - 1], programs[i
					+ 1]), stock, i);
		else
			pipe_data->pids[pipe_data->p++] = execute_program(programs[i], envp,
					pipe_data, next_exists);
		if (pipe_data->last_fd != STDIN_FILENO)
			close(pipe_data->last_fd);
		if (next_exists)
		{
			close(pipe_data->pipefd[1]);
			pipe_data->last_fd = pipe_data->pipefd[0];
		}
	}
}
