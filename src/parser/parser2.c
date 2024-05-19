/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:13:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 10:36:23 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection_parser2(int type)
{
	return (type == NODE_REDIRECTION_OUT || type == NODE_REDIRECTION_IN
		|| type == NODE_REDIRECTION_APPEND);
}

static void	_node_redir_helper(t_ast_node *current, t_arena *arena, \
		t_cmd_data *data, int *f_flag)
{
	if (*f_flag != 0)
	{
		while (current->left != NULL)
			current = current->left;
		current->left = create_node_tree(arena, NODE_ARGUMENT,
				data->token->data);
		if (data->prev_token->type == TOKEN_REDIR_OUT)
			current->left->f_out = 1;
		if (data->prev_token->type == TOKEN_REDIR_APPEND)
			current->left->f_out = 2;
	}
	else
	{
		while (current->right != NULL)
			current = current->right;
		current->right = create_node_tree(arena, NODE_ARGUMENT,
				data->token->data);
	}
}

void	_node_redir(t_arena *arena, t_ast_node **root, t_cmd_data *data,
		int *f_flag)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_ARGUMENT, data->token->data);
	if (!current->left && data->prev_token->type == TOKEN_REDIR_OUT)
		current->left = create_node_tree(arena, NODE_ARGUMENT,
				data->token->data);
	else if (!current->right && data->prev_token->type == TOKEN_WORD)
		current->right = new_node;
	else
		_node_redir_helper(current, arena, data, f_flag);
}
