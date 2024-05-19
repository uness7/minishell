/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:05:31 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 10:05:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir_out(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;

	new_node = create_node_tree(arena, NODE_REDIRECTION_OUT, data);
	if (*root == NULL)
		*root = new_node;
	else if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->right = temp;
	}
	else if ((*root)->type == NODE_REDIRECTION_IN)
	{
		temp = (*root)->left;
		if (temp->right && temp->left)
		{
			new_node->f_out = 1;
			temp->right = new_node;
		}
	}
	else if ((*root)->type == NODE_PIPELINE)
		(*root)->left = new_node;
}
