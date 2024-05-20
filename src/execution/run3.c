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

/* t_triple_programs {curr, next, prev} */
void	handle_builtin(t_program_state *state, t_stock *stock, int i)
{
	char	*new_input;
	int		saved_stdout;
	int		saved_stderr;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
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
		_runbuiltins(stock, new_input);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stderr);
}
