/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:05:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 10:28:39 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipeline(t_arena *arena, t_ast_node **root, t_node *token)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_PIPELINE, token->data);
	if (current)
	{
		*root = new_node;
		new_node->right = current;
	}
}
