/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_simple.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:25:08 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 10:37:01 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	_node_heredoc_helper(t_arena *arena, t_ast_node *current, \
		t_cmd_data *data)
{
	t_ast_node	*temp;

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

void	_node_heredoc(t_arena *arena, t_ast_node **root, t_cmd_data *data)
{
	t_ast_node	*current;
	t_ast_node	*new;

	current = *root;
	new = create_node_tree(arena, NODE_ARGUMENT, data->token->data);
	if (data->prev_token->type == TOKEN_REDIR_HEREDOC)
	{
		if (current->right == NULL)
			current->right = new;
		else
		{
			while (current->right != NULL)
				current = current->right;
			current->right = new;
		}
	}
	else if (data->prev_token->type == TOKEN_WORD)
		_node_heredoc_helper(arena, current, data);
	else if (data->prev_token->type == TOKEN_REDIR_OUT)
	{
		while (current->left != NULL)
			current = current->left;
		current->left = new;
		current->left->f_out = 1;
	}
}

void	parse_command_simple(t_arena *arena, t_ast_node **root,
		t_cmd_data *data, int *f_flag)
{
	if (is_redirection_parser2((*root)->type))
		_node_redir(arena, root, data, f_flag);
	else if ((*root)->type == NODE_REDIRECTION_HEREDOC)
		_node_heredoc(arena, root, data);
}
