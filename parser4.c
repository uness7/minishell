#include "minishell.h"
/*

static void     parse_command_pipeline(t_arena *arena, t_ast_node *current, t_node *token, int f_flag)
{
	// root->type == NODE_PIPELINE is always true
	// root->left != NULL	
	// root->right == NULL
	t_ast_node	*temp;

	if (current->right == NULL)
	{
		if (token->type == TOKEN_WORD)
		{
			if (f_flag == 1)
				current->right  = create_node_tree(arena, NODE_COMMAND, token->data);
		}
		else if (token->type == TOKEN_REDIR_OUT)
		{
			if (!current->left && !current->right)
				current->right->left = create_node_tree(arena, NODE_ARGUMENT, token->data);
			else if (current->left && !current->right)
				current->right->right = create_node_tree(arena, NODE_COMMAND, token->data);
			else if (!current->left && current->right)
				current->right->left = create_node_tree(arena, NODE_ARGUMENT, token->data);
			else
			{
				while (current->right != NULL)
					current = current->right;
				current->right = create_node_tree(arena, NODE_ARGUMENT, token->data);
			}
		}
	}
	else
	{
		if (token->type == TOKEN_WORD && !current->right->left)		
			current->right->left = create_node_tree(arena, NODE_ARGUMENT, token->data);
		else if (token->type == TOKEN_WORD && !current->right->right)
			current->right->right = create_node_tree(arena, NODE_ARGUMENT, token->data);
		else
		{
			if (f_flag == 0)
			{
				while (current->right != NULL)
					current = current->right;
				current->right = create_node_tree(arena, NODE_ARGUMENT, token->data);
			}
			else
			{
				temp = current->right;
				while (temp->left != NULL)
					temp = temp->left;
				current->left = create_node_tree(arena, NODE_ARGUMENT, token->data);
			}
		}

	}
}

void	parse_pipeline(t_arena *arena, t_ast_node **tree, t_node *token)
{
	t_ast_node	*new_node;
	t_ast_node	*temp;

	new_node = create_node_tree(arena, NODE_PIPELINE, token->data);

	temp = *tree;
	*tree = new_node;
	new_node->left = temp;
}


static void     parse_command_simple(t_arena *arena, t_ast_node **root, char *data, int f_flag)
{
        t_ast_node      *current;
        t_ast_node      *new_node;

        current = *root;
        new_node = create_node_tree(arena, NODE_ARGUMENT, data);
        if (current->type == NODE_REDIRECTION_OUT || \
                        current->type == NODE_REDIRECTION_IN || \
                        current->type == NODE_REDIRECTION_APPEND)
        {
                if (!current->left && !current->right)
                        current->left = new_node;
                else if (current->left && !current->right)
                        current->right = new_node;
                else if (!current->left && current->right)
                        current->left = new_node;
                else
                {
                        if (f_flag != 0 && ft_strncmp(current->data, "-", 1) == 0)
                        {
                                while (current->left != NULL)
                                        current = current->left;
                                current->left = create_node_tree(arena, NODE_ARGUMENT, data);
                        }
                        else
                        {
                                while (current->right != NULL)
                                        current = current->right;
                                current->right = create_node_tree(arena, NODE_ARGUMENT, data);
                        }
                }
        }
}

void    parse_command(t_arena *arena, t_ast_node **root, t_node *token, int f_flag)
{
	t_ast_node      *current;

	current = *root;
	if (*root == NULL)
	{
		*root = create_node_tree(arena, NODE_COMMAND, token->data);
	}
	else if ((*root)->type == NODE_COMMAND)
	{
		(*root)->right = create_node_tree(arena, NODE_COMMAND, token->data);
	}
	else if (current->type == NODE_PIPELINE)
	{
		parse_command_pipeline(arena, current, token, f_flag);
	}
	else
	{
		parse_command_simple(arena, root, token->data, f_flag);
	}
}
*/
