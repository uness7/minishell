/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/04 12:58:59 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	parse_redir_out(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;

	new_node = create_node_tree(arena, NODE_REDIRECTION_OUT, data);
	if (*root == NULL)
	{
		*root = new_node;
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->right = temp;
	}
	else if ((*root)->type == NODE_PIPELINE)
	{
		if ((*root)->right == NULL)
			(*root)->right = new_node;
		else
		{
			temp = (*root)->right;
			while (temp->left != NULL)
				temp = temp->left;
			temp->left = new_node;
		}
	}
}

static void	parse_redir_append(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;

	new_node = create_node_tree(arena, NODE_REDIRECTION_APPEND, data);
	if (*root == NULL)
	{
		*root = new_node;
	}
	if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->right = temp;
	}
	else if ((*root)->type == NODE_PIPELINE)
	{
		temp = find_mostleft_cmd(root);
		(*root)->left = new_node;
		new_node->right = temp;
	}
}

static void	parse_redir_in(t_arena *arena, t_ast_node **root, char *data)
{
	t_ast_node	*temp;
	t_ast_node	*new_node;

	new_node = create_node_tree(arena, NODE_REDIRECTION_IN, data);
	if (*root == NULL)
	{
		*root = new_node;
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		temp = *root;
		*root = new_node;
		new_node->right = temp;
	}
	else if ((*root)->type == NODE_PIPELINE)
	{
		temp = find_mostleft_cmd(root);
		(*root)->left = new_node;
		new_node->right = temp;
	}
}

static t_ast_node	*dispenser(t_arena *arena, t_node *temp_node)
{
	t_ast_node	*tree;
	t_node		*prev_token;
	int			f_flag;

	f_flag = 0;
	tree = NULL;
	while (temp_node != NULL)
	{
		if ((prev_token->type == TOKEN_REDIR_OUT
				|| prev_token->type == TOKEN_REDIR_IN
				|| prev_token->type == TOKEN_REDIR_APPEND)
			&& temp_node->type == TOKEN_WORD)
			f_flag = 1;
		if (temp_node->type == TOKEN_WORD)
		{
			parse_command(arena, &tree, temp_node, f_flag);
		}
		else if (temp_node->type == TOKEN_PIPE)
		{
			parse_pipeline(arena, &tree, temp_node);
		}
		else if (temp_node->type == TOKEN_REDIR_OUT)
		{
			parse_redir_out(arena, &tree, temp_node->data);
		}
		else if (temp_node->type == TOKEN_REDIR_APPEND)
		{
			parse_redir_append(arena, &tree, temp_node->data);
		}
		else if (temp_node->type == TOKEN_REDIR_IN)
		{
			parse_redir_in(arena, &tree, temp_node->data);
		}
		else if (temp_node->type == TOKEN_REDIR_HEREDOC)
		{
			parse_redir_heredoc(arena, &tree, temp_node->data);
		}
		prev_token = temp_node;
		temp_node = temp_node->next;
	}
	return (tree);
}

t_ast_node	*parse(t_arena *arena, t_list *stream)
{
	t_node	*temp_node;

	temp_node = stream->head;
	return (dispenser(arena, temp_node));
}
*/
