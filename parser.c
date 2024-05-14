/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/14 11:59:11 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if ((*root)->type == NODE_REDIRECTION_IN)
	{
		temp = (*root)->left;
		if (temp->right && temp->left)
		{
			new_node->f_out = 1;
			temp->right = new_node;
		}
	}
	else if ((*root)->type == NODE_PIPELINE)
	{
		if ((*root)->right == NULL)
			(*root)->right = new_node;
		else
		{
			if ((*root)->right->type == NODE_COMMAND) 
			{
				temp = (*root)->right;
				(*root)->right = new_node;
				new_node->right = temp;
			}
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

static t_ast_node	*dispenser(t_arena *arena, t_list *list)
{
	t_ast_node	*tree;
	t_node		*prev_token = NULL;
	int			f_flag;

	f_flag = 0;
	tree = NULL;
	while (list->head != NULL)
	{
		if (prev_token != NULL && (prev_token->type == TOKEN_REDIR_OUT
				|| prev_token->type == TOKEN_REDIR_IN
				|| prev_token->type == TOKEN_REDIR_APPEND
				|| prev_token->type == TOKEN_REDIR_HEREDOC)
			&& list->head->type == TOKEN_WORD)
			f_flag = 1;
		if (list->head->type == TOKEN_WORD)
		{
			parse_command(arena, &tree, list->head, prev_token, f_flag, list);
		}
		else if (list->head->type == TOKEN_PIPE)
		{
			parse_pipeline(arena, &tree, list->head);
		}
		else if (list->head->type == TOKEN_REDIR_OUT)
		{
			parse_redir_out(arena, &tree, list->head->data);
		}
		else if (list->head->type == TOKEN_REDIR_APPEND)
		{
			parse_redir_append(arena, &tree, list->head->data);
		}
		else if (list->head->type == TOKEN_REDIR_IN)
		{
			parse_redir_in(arena, &tree, list->head->data);
		}
		else if (list->head->type == TOKEN_REDIR_HEREDOC)
		{
			parse_redir_heredoc(arena, &tree, list->head->data);
		}
		f_flag = 0;
		prev_token = list->head;
		if (list->head != NULL)
			list->head = list->head->next;
	}
	return (tree);
}

t_ast_node	*parse(t_arena *arena, t_list *stream)
{
	return (dispenser(arena, stream));
}
