/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:47 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 16:41:36 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This file contains the functions of tree data structure like print_tree and such */

t_ast_node	*create_node_tree(bool arg_flag, t_token_type type, const char *data)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (new_node == NULL)
	{
		printf("Error allocating memory :0.\n");
		return (NULL);
	}
	if (type == TOKEN)
	{
		if (arg_flag == true)
		{
			new_node->type = NODE_ARGUMENT;
			new_node->data.argument = strdup(data);
			if (new_node->data.argument == NULL)
			{
				printf("Error allocating memroy:0 weird.\n");
				free(new_node);
				return (NULL);
			}
			new_node->left = NULL;
			new_node->right = NULL;
		}
		else
		{
			new_node->type = NODE_COMMAND;
			new_node->data.command = strdup(data);
			if (new_node->data.command == NULL)
			{
				printf("Error allocating memory :0.\n");
				free(new_node);
				return (NULL);
			}
			new_node->left = NULL;
			new_node->right = NULL;
		}
		return (new_node);
	}
	else if (type == TOKEN_PIPE)
	{
		new_node->type = NODE_PIPELINE;	
		new_node->left = NULL;
		new_node->right = NULL;
		return (new_node);
	}
	else
	{
		printf("Token is not known\n");
		free(new_node);
	}
	return (NULL);
}

void	print_tree(t_ast_node* root, int depth)
{
	int	i = 0;

	if (root == NULL)
		return;
	while (i < depth) {
		printf("  ");
		i++;
	}

	if (root->type == NODE_PIPELINE)
		printf("PIPELINE\n");
	if (root->type == NODE_COMMAND)
		printf("COMMAND: %s\n", root->data.command);
	else if (root->type == NODE_ARGUMENT)
		printf("ARGUMENT: %s\n", root->data.argument);
	print_tree(root->left, depth + 1);
	print_tree(root->right, depth + 1);
}
