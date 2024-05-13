/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:13:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/04 13:01:40 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	parse_command_simple(t_arena *arena, t_ast_node **root, char *data, int f_flag)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_ARGUMENT, data);
	if (current->type == NODE_REDIRECTION_OUT || \
			current->type == NODE_REDIRECTION_IN || \
			current->type == NODE_REDIRECTION_APPEND)
	{
		if (!current->left && !current->right)
			current->left = new_node;
		else if (current->left && !current->right)
			current->right = new_node;
		else if (!current->left && current->right)
			current->left = new_node;
		else
		{
			if (f_flag != 0 && ft_strncmp(current->data, "-", 1) == 0)
			{
				while (current->left != NULL)
					current = current->left;
				current->left = create_node_tree(arena, NODE_ARGUMENT, data);
			}
			else
			{
				while (current->right != NULL)
					current = current->right;
				current->right = create_node_tree(arena, NODE_ARGUMENT, data);
			}
		}
	}
}
static void	parse_command_pipeline(t_arena *arena, t_ast_node *current,
		char *data)
{
	if (current->left && current->left->type == NODE_COMMAND)
	{
		while (current->left != NULL)
			current = current->left;
		current->left = create_node_tree(arena, NODE_ARGUMENT, data);
	}
	else
	{
		while (current->left != NULL)
			current = current->left;
		current->left = create_node_tree(arena, NODE_COMMAND, data);
	}
}

void	parse_command(t_arena *arena, t_ast_node **root, char *data, int f_flag)
{
	t_ast_node	*current;

	current = *root;
	if (*root == NULL)
	{
		*root = create_node_tree(arena, NODE_COMMAND, data);
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		(*root)->right = create_node_tree(arena, NODE_COMMAND, data);
	}
	else if (current->type == NODE_PIPELINE)
	{
		parse_command_pipeline(arena, current, data);
	}
	else
	{
		parse_command_simple(arena, root, data, f_flag);
	}
}

void	parse_pipeline(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_PIPELINE, data);
	if (current)
	{
		*root = new_node;
		new_node->right = current;
	}
}

t_ast_node	*find_mostleft_cmd(t_ast_node **root)
{
	t_ast_node	*current;
	t_ast_node	*last_node;

	current = *root;
	while (current->left != NULL)
	{
		if (current->left->type == NODE_COMMAND)
			last_node = current->left;
		current = current->left;
	}
	return (last_node);
}

*/
