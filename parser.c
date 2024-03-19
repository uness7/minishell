/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 16:53:05 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token_type type, t_ast_node *root, const char *data)
{
	bool		arg_flag;
	t_ast_node	*current_node;

	if (root == NULL || root->type == NODE_PIPELINE)
	{
		arg_flag = false;
		if (root == NULL)
			root = create_node_tree(arg_flag, type, data);
		else
			root->right = create_node_tree(arg_flag, type, data);
	}
	else if (root->left == NULL)
	{
		arg_flag = true;
		root->left = create_node_tree(arg_flag, type, data);
		
	}
	else if (root->right == NULL)
	{
		arg_flag = true;
		root->right = create_node_tree(arg_flag, type, data);
	}
	else
	{
		arg_flag = true;
		current_node = root->left;
		while (current_node->right != NULL)
			current_node = current_node->right;
		current_node->right = create_node_tree(arg_flag, type, data);
	}
	return (root);
}

t_ast_node	*parse_pipeline(t_token_type type, t_ast_node *root, const char *data)
{
	t_ast_node	*new_node;
	t_ast_node	*new_root;
	bool		arg_flag;

	arg_flag = false;
	new_node = create_node_tree(arg_flag, type, data);
	if (root == NULL)
	{
		printf("Error tree is empty or pipe was used incorrectly\n");
		exit(1);
	}
	if (root->type == NODE_PIPELINE)
		root->right = new_node;
	else
	{
		new_root = create_node_tree(arg_flag, type, data);
		new_root->left = root;
		new_root->right = new_node;
		root = new_root;
	}
	return (root);	
}

/*
t_ast_node	*parse_redirction()
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
		if (temp_node->type == TOKEN)
		{
			tree = parse_command(temp_node->type, tree, temp_node->data);
		}
		else if (temp_node->type == TOKEN_PIPE)
		{
			tree = parse_pipeline(temp_node->type, tree, temp_node->data);
		}
		temp_node = temp_node->next;
	}
	return (tree);
}
