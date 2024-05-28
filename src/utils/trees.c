/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:47 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/28 00:22:08 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node_tree(t_arena *arena, t_node_type type, char *data)
{
	t_ast_node	*new_node;

	new_node = arena_alloc(arena, sizeof(t_ast_node));
	new_node->type = type;
	if (data != NULL)
	{
		if (ft_strstr(data, "\"") == 0 || ft_strstr(data, "'") == 0)
			new_node->data = ft_strdup(arena, ign_quotes(arena, data));
		else
			new_node->data = ft_strdup(arena, data);
	}
	if (new_node->data == NULL)
	{
		printf("Error allocating memroy:0.\n");
		return (NULL);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->f_out = 0;
	return (new_node);
}

void	print_tree_utils(t_ast_node *root, int space)
{
	int	i;

	if (root == NULL)
		return ;
	space += 10;
	print_tree_utils(root->right, space);
	printf("\n");
	i = -1;
	while (++i < space)
		printf(" ");
	if (root->type == NODE_PIPELINE)
		printf("PIPELINE\n");
	else if (root->type == NODE_REDIRECTION_OUT)
		printf("REDIR.OUT\n");
	else if (root->type == NODE_REDIRECTION_APPEND)
		printf("APPEND\n");
	else if (root->type == NODE_REDIRECTION_IN)
		printf("REDIR.IN\n");
	else if (root->type == NODE_REDIRECTION_HEREDOC)
		printf("HEREDOCC\n");
	else if (root->data != NULL)
		printf("%s\n", root->data);
	else
		printf("(null)\n");
	print_tree_utils(root->left, space);
}

void	print_tree(t_ast_node *root)
{
	print_tree_utils(root, 0);
}

/*
void	print_programs(t_program **programs, int count)
{
	if (programs == NULL)
	{
		printf("The programs array is NULL.\n");
		return ;
	}
	for (int i = 0; i < count; ++i)
	{
		if (programs[i] == NULL)
		{
			printf("Program %d is NULL.\n", i + 1);
			continue ;
		}
		printf("Program %d Details:\n", i + 1);
		printf("Type: %d\n", programs[i]->type);
		printf("fd_out: %d\n", programs[i]->fd_out);
		printf("fd_in: %d\n", programs[i]->fd_in);
		printf("fd_heredoc: %d\n", programs[i]->fd_heredoc);
		printf("Args:\n");
		if (programs[i]->args)
		{
			for (int j = 0; programs[i]->args[j] != NULL; j++)
			{
				printf("  arg[%d]: %s\n", j, programs[i]->args[j]);
			}
		}
		else
		{
			printf("  No arguments.\n");
		}
		printf("Cmd: %s\n",
			programs[i]->cmd ? programs[i]->cmd : "No command.");
		printf("\n");
	}
}
*/
