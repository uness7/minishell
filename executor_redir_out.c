/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:29:31 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/30 16:10:39 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_cmd	*extract_data(t_arena *arena, t_ast_node *root,
		t_redir_cmd *result)
{
	result->av = build_command(arena, root->right);
	if (root == NULL || root->left == NULL || root->left->data == NULL)
	{
		printf("Syntax error.\n");
		return (NULL);
	}
	result->target = ft_strdup(arena, root->left->data);
	if (result->target == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	return (result);
}

t_redir_cmd	*build_cmd_redir_out(t_arena *arena, t_ast_node *root)
{
	t_redir_cmd	*result;

	result = arena_alloc(arena, sizeof(t_redir_cmd));
	if (result == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	return (extract_data(arena, root, result));
}

int	execute_redir_out(t_stock *stock, char *cmd_path, char *target, char **av)
{
	pid_t	id;
	int		status;
	int		fd;

	fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		open_err();
	status = 0;
	id = fork();
	if (id == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(cmd_path, av, stock->envp);
		execve_err(stock->arena, stock->env);
	}
	else if (id < 0)
		fork_err();
	else
		wait(&status);
	close(fd);
	return (WEXITSTATUS(status));
}
