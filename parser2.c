/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:13:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/13 20:00:28 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_command_simple(t_arena *arena, t_ast_node **root, t_node *token, \
		t_node *prev_token, int *f_flag)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_ARGUMENT, token->data);
	if (current->type == NODE_REDIRECTION_OUT || \
			current->type == NODE_REDIRECTION_IN || \
			current->type == NODE_REDIRECTION_APPEND)
	{
		if (!current->left && prev_token->type == TOKEN_REDIR_OUT)
			current->left = new_node;
		else if (!current->right && prev_token->type == TOKEN_WORD)
			current->right = new_node;
		else
		{
			if (*f_flag != 0)
			{
				while (current->left != NULL)
					current = current->left;
				current->left = create_node_tree(arena, NODE_ARGUMENT, token->data);
			}
			else
			{
				while (current->right != NULL)
					current = current->right;
				current->right = create_node_tree(arena, NODE_ARGUMENT, token->data);
			}
		}
	}
	else if (current->type == NODE_REDIRECTION_HEREDOC)
	{
		if (prev_token->type == TOKEN_REDIR_HEREDOC)
		{
			while (current->right != NULL)
				current = current->right;
			current->right = create_node_tree(arena, NODE_ARGUMENT, \
					token->data);
		}
	}
}

static t_ast_node	*parse_command_pipeline(t_arena *arena, t_ast_node *current,
		char *data, t_list *list)
{
	t_ast_node	*subtree = NULL;
	(void)data;
	(void)current;
	subtree = parse(arena, list);
	return subtree;
}

void	parse_command(t_arena *arena, t_ast_node **root, t_node *token, \
		t_node *prev_token, int f_flag, t_list *list)
{
	t_ast_node	*temp;
	t_ast_node	*current;
	t_ast_node	*subtree = NULL;

	current = *root;
	if (*root == NULL)
	{
		*root = create_node_tree(arena, NODE_COMMAND, token->data);
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		temp = (*root)->right;
		if (temp == NULL)
			(*root)->right = create_node_tree(arena, NODE_COMMAND, token->data);
		else 
		{
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = create_node_tree(arena, NODE_COMMAND, token->data);
		}
	}
	else if (current->type == NODE_PIPELINE)
	{
		subtree = parse_command_pipeline(arena,NULL,NULL, list);
		(*root)->left = subtree;
	}
	else
	{
		parse_command_simple(arena, root, token, prev_token, &f_flag);
	}
}

void	parse_pipeline(t_arena *arena, t_ast_node **root, t_node *token)
{
	t_ast_node	*current;
	t_ast_node	*new_node;

	current = *root;
	new_node = create_node_tree(arena, NODE_PIPELINE, token->data);
	if (current)
	{
		*root = new_node;
		new_node->right = current;
	}
}

t_ast_node	*find_mostleft_cmd(t_ast_node **root)
{
	t_ast_node	*current;
	t_ast_node	*last_node;

	current = *root;
	while (current->left != NULL)
	{
		if (current->left->type == NODE_COMMAND)
			last_node = current->left;
		current = current->left;
	}
	return (last_node);
}
