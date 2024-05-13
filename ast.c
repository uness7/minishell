#include "minishell.h"

t_ast_node	*parse_cmd(t_arena *arena, t_node *token, t_node *prev_token)
{
	static t_ast_node	*tree = NULL;
	t_ast_node			*new_node;
	t_ast_node			*temp;

	new_node = NULL;
	if (!prev_token && token->type == TOKEN_WORD)
	{
		new_node = create_node_tree(arena, NODE_COMMAND, token->data);
		tree = new_node;
	}
	else if (prev_token && prev_token->type == TOKEN_WORD
		&& token->type == TOKEN_WORD)
	{
		new_node = create_node_tree(arena, NODE_ARGUMENT, token->data);
		if (tree->right == NULL)
			tree->right = new_node;
		else
		{
			temp = tree->right;
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = new_node;
		}
	}
	return (tree);
}

t_ast_node	*parse_redir_out(t_arena *arena, t_ast_node **tree, t_node *token, t_node *prev_token)
{
	t_ast_node	*new = NULL;
	t_ast_node	*temp = NULL;

	(void)prev_token;
	new = create_node_tree(arena, NODE_REDIRECTION_OUT, token->data);
	if (*tree == NULL)
		*tree = new;
	else
	{
		if ((*tree)->type == NODE_COMMAND)
		{
			temp = *tree;
			*tree = new;
			new->right = temp;
		}
	}
	return (*tree);
}

t_ast_node	*ast(t_arena *arena, t_list *tokens)
{
	t_node		*token;
	t_node		*prev_token;
	t_ast_node	*tree;

	token = tokens->head;
	prev_token = NULL;
	tree = NULL;
	while (token != NULL)
	{
		if (token->type == TOKEN_WORD)
			tree = parse_cmd(arena, token, prev_token);
		else if (token->type == TOKEN_REDIR_OUT)
			tree = parse_redir_out(arena, &tree, token, prev_token);
		prev_token = token;
		token = token->next;
	}
	return (tree);
}
