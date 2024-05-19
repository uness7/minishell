/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:04:55 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 10:04:56 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(int type)
{
	return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static void	_node_cmd(t_arena *arena, t_ast_node *temp, t_ast_node **root,
		t_cmd_data *data)
{
	temp = (*root)->right;
	if (temp == NULL)
	{
		(*root)->right = create_node_tree(arena, NODE_COMMAND,
				data->token->data);
	}
	else
	{
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = create_node_tree(arena, NODE_COMMAND, data->token->data);
	}
}

static void	_node_pipeline(t_arena *arena, t_ast_node **root, t_cmd_data *data)
{
	t_ast_node	*subtree;

	subtree = NULL;
	if (is_redirection(data->prev_token->type))
		add_node_to_front(data->list, data->prev_token);
	subtree = parse_command_pipeline(arena, NULL, NULL, data->list);
	(*root)->left = subtree;
}

void	parse_command(t_arena *arena, t_ast_node **root, t_cmd_data *data,
		int f_flag)
{
	t_ast_node	*temp;
	t_ast_node	*current;

	current = *root;
	temp = NULL;
	if (*root == NULL)
		*root = create_node_tree(arena, NODE_COMMAND, data->token->data);
	else if ((*root)->type == NODE_COMMAND)
		_node_cmd(arena, temp, root, data);
	else if (current->type == NODE_PIPELINE)
		_node_pipeline(arena, root, data);
	else
		parse_command_simple(arena, root, data, &f_flag);
}

t_ast_node	*parse_command_pipeline(t_arena *arena, t_ast_node *current,
		char *data, t_list *list)
{
	t_ast_node	*subtree;

	subtree = NULL;
	(void)data;
	(void)current;
	subtree = parse(arena, list);
	return (subtree);
}
