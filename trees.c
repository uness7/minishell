#include "minishell.h"

/* This file contains the functions of tree data structure like print_tree and such */

t_ast_node	*create_node_tree(const char *data)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (new_node == NULL)
	{
		printf("Error allocating memory :0.\n");
		return (NULL);
	}
	new_node->type = NODE_COMMAND;
	new_node->data.command = strdup(data);
	if (new_node->data.command == NULL)
	{
		printf("Error allocating memory :0.\n");
		return (NULL);
	}
	return (new_node);
}

void	print_tree_helper(t_ast_node *node, int depth)
{
	if (node == NULL)
	{
		return ;
	}
	// Print current node
	for (int i = 0; i < depth; i++)
	{
		printf("  "); // Indentation for better visualization
	}
	switch (node->type)
	{
	case NODE_COMMAND:
		printf("Command: %s\n", node->data.command);
		break ;
	case NODE_ARGUMENT:
		printf("Argument: %s\n", node->data.argument);
		break ;
	case NODE_PIPELINE:
		printf("Pipeline\n");
		break ;
	case NODE_REDIRECTION:
		printf("Redirection: %s %s\n", node->data.redirection.operator,
			node->data.redirection.filename);
		break ;
		// Add cases for other node types as needed
	}
	// Recursively print children
	/*
	if (node->type == NODE_PIPELINE)
	{
		print_tree_helper(node->pipeline.left, depth + 1);
		print_tree_helper(node->pipeline.right, depth + 1);
	}
	*/
}

void	print_tree(t_ast_node *root)
{
	printf("Abstract Syntax Tree:\n");
	print_tree_helper(root, 0);
}
