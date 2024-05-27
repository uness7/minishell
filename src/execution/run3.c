/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:38:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/27 23:36:59 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_run_builtin(t_program *prev, t_program *next,
		t_program *curr, int i)
{
	if (prev && next && ft_strcmp(curr->cmd, "echo") == 0 && i != 0)
		return (true);
	else if ((i == 0 && ft_strcmp(curr->cmd, "echo") != 0) || (!next
			&& (ft_strcmp(curr->cmd, "echo") == 0 || ft_strcmp(curr->cmd,
					"pwd") == 0)))
		return (true);
	return (false);
}

int	handle_builtin(t_program_state *state, t_stock *stock, int i)
{
	char	*new_input;
	int		saved_stdout;
	int		status;

	status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	if (state->curr->fd_out != STDOUT_FILENO)
	{
		dup2(state->curr->fd_out, STDOUT_FILENO);
		close(state->curr->fd_out);
	}
	if (state->curr->fd_in != STDIN_FILENO)
	{
		dup2(state->curr->fd_in, STDIN_FILENO);
		close(state->curr->fd_in);
	}
	if (should_run_builtin(state->prev, state->next, state->curr, i))
	{
		new_input = join_args(stock->arena, state->curr->args);
		stock->last_open_fd = saved_stdout;
		status = _runbuiltins(stock, new_input);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (status);
}

char	*change_path_run(t_stock *stock, char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*path;
	char	*new_cmd;

	i = 0;
	j = 0;
	k = 0;
	path = arena_alloc(stock->arena, ft_strlen(cmd) + 1);
	new_cmd = arena_alloc(stock->arena, ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		if (cmd[i] == '.' || cmd[i] == '/')
			path[j++] = cmd[i];
		else
			break ;
		i++;
	}
	path[j] = '\0';
	while (cmd[i])
		new_cmd[k++] = cmd[i++];
	new_cmd[k] = '\0';
	ft_cd(stock->arena, path, stock->env);
	return (new_cmd);
}
