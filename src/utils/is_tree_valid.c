/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tree_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:50:34 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 17:51:53 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_tree_valid(t_ast_node *root)
{
	if (root == NULL)
		return (true);
	if (root->type == NODE_PIPELINE)
	{
		if (root->left == NULL || root->right == NULL)
			return (false);
	}
	return (true);
}
