/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/21 11:50:51 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_ast_node **root, const char *data)
{
	t_ast_node	*current;

	current = *root;
	if (*root == NULL)
		*root = create_node_tree(NODE_COMMAND, data);
	else
	{
		if (current->right == NULL)
			(*root)->right = create_node_tree(NODE_ARGUMENT, data);
		else if (current->left == NULL)
			(*root)->left = create_node_tree(NODE_ARGUMENT, data);
		else
		{
			while (current->right != NULL)
				current = current->right;
			current->right = create_node_tree(NODE_ARGUMENT, data);	
		}
	}
	return (*root);
}

t_ast_node	*parse_pipeline(t_ast_node **root, char *data)
{
	t_ast_node	*node;
	t_ast_node	*new_root;

	node = create_node_tree(NODE_PIPELINE, data);
	if (*root == NULL)
	{
		printf("Error tree is empty or pipe was used incorrectly\n");
		free(node);
		return (NULL);
	}
	if ((*root)->type == NODE_PIPELINE)
		(*root)->right = node;
	else
	{
		new_root = create_node_tree(NODE_COMMAND, data);
		new_root->left = *root;
		new_root->right = node;
		*root = new_root;
	}
	return (*root);
}

/*
t_ast_node	*parse_redirction(void)
{
}
*/

t_ast_node	*parse(t_list *stream)
{
	t_ast_node	*tree;
	t_node		*temp_node;

	tree = NULL;
	temp_node = stream->head;
	while (temp_node != NULL)
	{
		if (temp_node->type == TOKEN_WORD)
			tree = parse_command(&tree, temp_node->data);
		temp_node = temp_node->next;
	}
	return (tree);
}
