/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isTreeValid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:13:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/17 16:13:09 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redir_valid(t_ast_node *tree)
{
	if (tree->left == NULL || tree->right == NULL)
		return (false);
	return (true);
}

static bool	is_heredoc_valid(t_ast_node *tree)
{
	if (tree->left && !tree->right)
		return (false);
	return (true);
}
bool is_tree_valid(t_ast_node *tree) {
    // Base case: if the tree is NULL, it is considered invalid
    if (tree == NULL) {
        return false;
    }

    // Check if the current node is a redirection node
    if (tree->type == NODE_REDIRECTION_OUT ||
        tree->type == NODE_REDIRECTION_IN ||
        tree->type == NODE_REDIRECTION_APPEND) {
        // Validate the redirection node
        if (!is_redir_valid(tree)) {
            return false;
        }
    }
    // Check if the current node is a heredoc node
    else if (tree->type == NODE_REDIRECTION_HEREDOC) {
        // Validate the heredoc node
        if (!is_heredoc_valid(tree)) {
            return false;
        }
    }
    // Check if the current node is a pipeline node
    else if (tree->type == NODE_PIPELINE) {
        // Validate the pipeline node by ensuring both left and right children are valid
        if (!is_tree_valid(tree->left) || !is_tree_valid(tree->right)) {
            return false;
        }
    }

    // Recursively check the left and right children of the current node
    if (tree->left && !is_tree_valid(tree->left)) {
        return false;
    }
    if (tree->right && !is_tree_valid(tree->right)) {
        return false;
    }

    // If all checks pass, the tree is valid
    return true;
}
