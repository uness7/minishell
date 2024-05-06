/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:47 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/04 12:31:37 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node_tree(t_arena *arena, t_node_type type, char *data)
{
	t_ast_node	*new_node;

	new_node = arena_alloc(arena, sizeof(t_ast_node));
	if (new_node == NULL)
	{
		printf("Error allocating memory :0.\n");
		return (NULL);
	}
	new_node->type = type;
	if (data != NULL)
		new_node->data = ft_strdup(arena, data);
	if (new_node->data == NULL)
	{
		printf("Error allocating memroy:0.\n");
		return (NULL);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	print_tree_utils(t_ast_node *root, int space)
{
	int		i;

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
		printf("APPEND");
	else if (root->type == NODE_REDIRECTION_IN)
		printf("REDIR.IN\n");
	else if (root->type == NODE_REDIRECTION_HEREDOC)
		printf("HEREDOCC\n");
	else if (root->data != NULL)
		printf("%s\t%d\n", root->data, root->type);
	else
		printf("(null)\n");
	print_tree_utils(root->left, space);
}

void	print_tree(t_ast_node *root)
{
	print_tree_utils(root, 0);
}
