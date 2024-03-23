/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/23 18:16:13 by yzioual          ###   ########.fr       */
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
		if (current->type == NODE_PIPELINE)
		{
			if (current->left && current->left->type == NODE_COMMAND)
			{
				while (current->left != NULL)
					current = current->left;
				current->left = create_node_tree(NODE_ARGUMENT, data);
			}
			else
			{
				while (current->left != NULL)
					current = current->left;
				current->left = create_node_tree(NODE_COMMAND, data);
			}
		}
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
	}
	return (*root);
}

t_ast_node	*parse_pipeline(t_ast_node **root, char *data)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(NODE_PIPELINE, data);
	if (current != NULL)
	{
		*root = new_node;
		new_node->right = current;
	}
	return (*root);
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

/* A function that returns the last node added that is of type NODE_COMMAND */
t_ast_node	*find_mostright_cmd(t_ast_node **root)
{
	t_ast_node      *current;
	t_ast_node      *last_node;

	last_node = NULL;
        current = *root;
        while (current->right != NULL)
	{
		if (current->type == NODE_COMMAND)
			last_node = current;
                current = current->right;
	}
        return (last_node);
}

t_ast_node	*parse_redir_out(t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;


	new_node = create_node_tree(NODE_REDIRECTION, data);
	if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->right = temp;
		return (*root);
	}
	else if ((*root)->type == NODE_PIPELINE)
	{
		temp = find_mostleft_cmd(root);
		(*root)->left = new_node;
		new_node->right = temp;
		return (*root);
	}
	return (*root);
}

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
		else if (temp_node->type == TOKEN_PIPE)
			tree = parse_pipeline(&tree, NULL);
		else if (temp_node->type == TOKEN_REDIR_OUT)
			parse_redir_out(&tree, temp_node->data);
		temp_node = temp_node->next;
	}
	return (tree);
}
