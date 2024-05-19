/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:13:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/17 00:23:53 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(int type)
{
	return (type == NODE_REDIRECTION_OUT || type == NODE_REDIRECTION_IN
		|| type == NODE_REDIRECTION_APPEND);
}

static void	_node_redir(t_arena *arena, t_ast_node **root, t_cmd_data *data,
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
}

static void	_node_heredoc(t_arena *arena, t_ast_node **root, t_cmd_data *data)
{
	t_ast_node	*temp;
	t_ast_node	*current;

	current = *root;
	if (data->prev_token->type == TOKEN_REDIR_HEREDOC)
	{
		if (current->right == NULL)
			current->right = create_node_tree(arena, NODE_ARGUMENT,
					data->token->data);
		else
		{
			while (current->right != NULL)
				current = current->right;
			current->right = create_node_tree(arena, NODE_ARGUMENT,
					data->token->data);
		}
	}
	else if (data->prev_token->type == TOKEN_WORD)
	{
		if (current->left == NULL)
			current->left = create_node_tree(arena, NODE_ARGUMENT,
					data->token->data);
		else
		{
			temp = current->left;
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = create_node_tree(arena, NODE_ARGUMENT,
					data->token->data);
		}
	}
	else if (data->prev_token->type == TOKEN_REDIR_OUT)
	{
		while (current->left != NULL)
			current = current->left;
		current->left = create_node_tree(arena, NODE_ARGUMENT,
				data->token->data);
		current->left->f_out = 1;
	}
}

void	parse_command_simple(t_arena *arena, t_ast_node **root,
		t_cmd_data *data, int *f_flag)
{
	if (is_redirection((*root)->type))
		_node_redir(arena, root, data, f_flag);
	else if ((*root)->type == NODE_REDIRECTION_HEREDOC)
		_node_heredoc(arena, root, data);
}
