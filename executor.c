/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:51:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/30 13:48:49 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_number_nodes(t_ast_node *root)
{
	int	number_nodes;

	number_nodes = 0;
	if (root == NULL)
		return (0);
	number_nodes++;
	number_nodes += find_number_nodes(root->left);
	number_nodes += find_number_nodes(root->right);
	return (number_nodes);
}

static void	right_side_root(t_arena *arena, t_ast_node *root, char **av,
		int *index)
{
	char	**right_args;

	right_args = build_command(arena, root->right);
	while (right_args && *right_args)
	{
		av[(*index)++] = ft_strdup(arena, *right_args++);
		if (av[(*index) - 1] == NULL)
		{
			printf("Error allocating memory\n");
			return ;
		}
	}
}

static void	left_side_root(t_arena *arena, t_ast_node *root, char **av,
		int *index)
{
	char	**left_args;

	left_args = build_command(arena, root->left);
	while (left_args && *left_args)
	{
		av[(*index)++] = ft_strdup(arena, *left_args++);
		if (av[(*index) - 1] == NULL)
		{
			printf("Error allocating memory\n");
			return ;
		}
	}
}

char	**build_command(t_arena *arena, t_ast_node *root)
{
	char	**av;
	int		number_args;
	int		index;

	number_args = find_number_nodes(root);
	av = arena_alloc(arena, sizeof(char *) * (number_args + 1));
	if (av == NULL)
	{
		printf("Error allocating memory \n");
		return (NULL);
	}
	av[0] = ft_strdup(arena, root->data);
	if (av[0] == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	index = 1;
	if (root->right != NULL)
		right_side_root(arena, root, av, &index);
	if (root->left != NULL)
		left_side_root(arena, root, av, &index);
	av[number_args] = NULL;
	return (av);
}

int	execute(t_stock *stock, char *cmd, char **av)
{
	pid_t	id;
	int		status;

	id = fork();
	status = 0;
	if (id == 0)
	{
		execve(cmd, av, stock->envp);
		execve_err(stock->arena, stock->env);
	}
	else if (id < 0)
		fork_err();
	else
		wait(&status);
	return (WEXITSTATUS(status));
}
