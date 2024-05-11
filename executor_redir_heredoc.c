/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:21:32 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/11 11:56:05 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_heredoc	*extract_data(t_arena *arena, t_ast_node *root,
		t_redir_heredoc *result, int *i)
{
	if (root->right)
	{
		result->av[*i] = arena_alloc(arena, sizeof(t_hd_arr));
		result->av[*i]->data = ft_strdup(arena, root->right->data);
		result->av[*i]->type = DELI;
		(*i)++;
	}
	if (root->left)
	{
		if (root->left->type == NODE_REDIRECTION_HEREDOC)
			result = extract_data(arena, root->left, result, i);
		else if (root->left->type == NODE_COMMAND)
		{
			if (root->left->data != NULL)
			{
				result->av[*i] = arena_alloc(arena, sizeof(t_hd_arr));
				result->av[*i]->data = ft_strdup(arena, root->left->data);
				result->av[*i]->type = CMD;
				(*i)++;
			}
			while (root->left->right != NULL)
			{
				result->av[*i] = arena_alloc(arena, sizeof(t_hd_arr));
				result->av[(*i)]->data = ft_strdup(arena, root->left->right->data);
				result->av[(*i)++]->type = ARG;
				root->left->right = root->left->right->right;
			}

		}
	}
	else
	{
		result->av[*i] = arena_alloc(arena, sizeof(t_hd_arr));
		result->av[*i]->data = ft_strdup(arena, "-1");
		result->av[*i]->type = NO_CMD;
		(*i)++;
	}
	result->av[*i] = NULL;
	return (result);
}

t_redir_heredoc	*build_cmd_redir_heredoc(t_arena *arena, t_ast_node *root)
{
	t_redir_heredoc	*result;
	int			i;

	i = 0;
	result = arena_alloc(arena, sizeof(t_redir_heredoc));
	result->av = arena_alloc(arena, 10 * sizeof(t_hd_arr *));
	return (extract_data(arena, root, result, &i));
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
