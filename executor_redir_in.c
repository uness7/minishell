/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 23:17:49 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_cmd	*extract_data(t_arena *arena, t_ast_node *root,
		t_redir_cmd *result)
{
	result->av = build_command(arena, root->right);
	if (root == NULL || root->left == NULL || root->left->data == NULL)
	{
		printf("Syntax error. \n");
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

t_redir_cmd	*build_cmd_redir_in(t_arena *arena, t_ast_node *root)
{
	t_redir_cmd	*result;

	result = arena_alloc(arena, sizeof(t_redir_cmd));
	if (result == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	return (result = extract_data(arena, root, result));
}

int	execute_redir_in(t_stock *stock, char *cmd, char *target, char **av)
{
	pid_t	id;
	int		status;
	int		fd;

	fd = -1;
	id = fork();
	status = 0;
	if (id == 0)
	{
		fd = open(target, O_RDONLY, 0644);
		if (fd == -1)
			open_err();
		dup2(fd, STDIN_FILENO);
		execve(cmd, av, stock->envp);
		execve_err(stock->arena, stock->env);
	}
	else if (id < 0)
		fork_err();
	else
		wait(&status);
	close(fd);
	return (WEXITSTATUS(status));
}
