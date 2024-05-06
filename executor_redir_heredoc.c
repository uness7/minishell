/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:21:32 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 17:57:42 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_heredoc	*extract_data(t_arena *arena, t_ast_node *root,
		t_redir_heredoc *result)
{
	result->av = build_command(arena, root->right);
	if (root->left == NULL || root->left->data == NULL)
		return (NULL);
	result->delimeter = ft_strdup(arena, root->left->data);
	if (result->delimeter == NULL)
		return (NULL);
	return (result);
}

t_redir_heredoc	*build_cmd_redir_heredoc(t_arena *arena, t_ast_node *root)
{
	t_redir_heredoc	*result;

	result = arena_alloc(arena, sizeof(t_redir_heredoc));
	return (extract_data(arena, root, result));
}

static void	write_input(char **input, int fd_in, int fd_out)
{
	close(fd_in);
	while (*input)
	{
		ft_putstr_fd(*input, fd_out);
		if (*(input + 1) != NULL)
			ft_putstr_fd("\n", fd_out);
		input++;
	}
	close(fd_out);
}

int	execute_redir_heredoc(t_stock *stock, char *cmd, char **input, char **av)
{
	pid_t	id;
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
		pipe_err();
	status = 0;
	id = fork();
	if (id == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(cmd, av, stock->envp);
		execve_err(stock->arena, stock->env);
	}
	else if (id < 0)
		fork_err();
	else
	{
		write_input(input, fd[0], fd[1]);
		waitpid(id, &status, WUNTRACED);
	}
	return (0);
}
