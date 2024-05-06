/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:33 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/30 16:09:49 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_cmd	*build_cmd_redir_append(t_arena *arena, t_ast_node *root)
{
	t_redir_cmd	*result;

	result = arena_alloc(arena, sizeof(t_redir_cmd));
	if (root == NULL || root->left == NULL || root->left->data == NULL)
	{
		printf("Syntax Error. \n");
		return (NULL);
	}
	if (root->left->type == NODE_ARGUMENT)
	{
		result->av = build_command(arena, root->right);
		result->target = ft_strdup(arena, root->left->data);
	}
	else
	{
		result->av = build_command(arena, root);
		result->target = ft_strdup(arena, root->right->data);
	}
	return (result);
}

int	execute_redir_append(t_stock *stock, char *cmd_path, char *target,
		char **av)
{
	pid_t	id;
	int		status;
	int		fd;

	fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open ");
		exit(EXIT_FAILURE);
	}
	status = 0;
	id = fork();
	if (id == 0)
	{
		dup2(fd, 1);
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
