/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isTreeValid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:17:05 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/16 13:38:34 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_root_valid(t_ast_node *root)
{
	if (root != NULL)
		return (true);
	return (false);
}

static bool	is_redir_valid(t_ast_node *root)	
{
	if (root->left != NULL && root->right != NULL)
		return (true);
	return (false);
}

static bool	is_heredoc_valid(t_ast_node *root)
{
	if (root->left != NULL)
		return (true);
	return (false);
}

static bool	is_pipeline_valid(t_ast_node *root)
{
	if (root->left != NULL && root->right != NULL)
		return (true);
	return (false);
}

bool	is_tree_valid(t_ast_node *root)
{
	if (!is_root_valid(root) && !is_redir_valid(root) \
			&& !is_heredoc_valid(root) \
			&& !is_pipeline_valid(root))
	{
		return (false);
	}
	return (true);
}
