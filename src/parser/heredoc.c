/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:47:57 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/15 21:26:28 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir_heredoc(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;

	new_node = create_node_tree(arena, NODE_REDIRECTION_HEREDOC, data);
	if (*root == NULL)
	{
		*root = new_node;
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->left = temp;
	}
}
