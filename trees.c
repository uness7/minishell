/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:47 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/21 11:46:22 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node_tree(t_node_type type, const char *data)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (new_node == NULL)
	{
		printf("Error allocating memory :0.\n");
		return (NULL);
	}
	new_node->type = type;
	if (type == NODE_COMMAND || type == NODE_ARGUMENT)
	{
		if (data != NULL)
			new_node->data = strdup(data);
		if (new_node->data == NULL)
		{
			printf("Error allocating memroy:0 weird.\n");
			free(new_node);
			return (NULL);
		}
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	print_tree_utils(t_ast_node *root, int space)
{
	if (root == NULL)
		return ;
	space += 10;
	print_tree_utils(root->right, space);
	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	if (root->type == NODE_PIPELINE)
		printf("PIPELINE\n");
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
