#include "minishell.h"

void	add_node_to_front(t_list *list, t_node *new_node)
{
	if (list == NULL || new_node == NULL)
		return ;
	new_node->next = list->head;
	list->head = new_node;
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
