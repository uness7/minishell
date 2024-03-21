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


/*
 * - When root is null, it indicates that the token is a command and an argument otherwise
 */ 

t_ast_node	*parse_command(t_ast_node **root, const char *data)
{
	t_ast_node	*node;

	if (*root == NULL)
	{
		node = create_node_tree(NODE_COMMAND, data);
		*root = node;
	}
	else
	{
		node = create_node_tree(NODE_ARGUMENT, data);
		if ((*root)->right == NULL)
			(*root)->right = node;
		else if ((*root)->left == NULL)
			(*root)->left = node;
	}
	return (*root);
}

t_ast_node	*parse_pipeline(t_ast_node **root, char *data)
{
	t_ast_node	*node;
	t_ast_node	*temp_node;
	t_ast_node	*new_root;

	node = create_node_tree(NODE_PIPELINE, data);
	if (*root == NULL)
	{
		printf("Error tree is empty or pipe was used incorrectly\n");
		free(node);
		return (NULL);
	}
	temp_node = *root;	
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
		if (temp_node->type == TOKEN_WORD)
		{
			tree = parse_command(&tree, temp_node->data);
		}
		else if (temp_node->type == TOKEN_PIPE)
		{
			tree = parse_pipeline(&tree, temp_node->data);
		}
		else
			printf("token not known");
		temp_node = temp_node->next;
	}
	return (tree);
}
