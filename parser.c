#include "minishell.h"

t_ast_node	*parse_command(t_ast_node *root, const char *data)
{
	if (root == NULL) 
	{
		root = create_node_tree(data);
	}
	return (root);
}

t_ast_node	*parse(t_list *stream)
{
	t_ast_node	*tree;
	t_node		*temp_node;

	tree = NULL;
	temp_node = stream->head;
	while (temp_node != NULL)
	{
		if (temp_node->type == TOKEN)
		{
			tree = parse_command(tree, temp_node->data);
		}
		else
		{
			printf("oooops\n");
			exit(1);
		}
		temp_node = temp_node->next;
	}
	return (tree);
}
