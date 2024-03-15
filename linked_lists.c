#include "minishell.h"

t_node	*create_node(char *data, t_token_type type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->type = type;
	new->data = data;
	new->next = NULL;
}

void	init_list(t_list *list)
{
	list->head = NULL;
}

void	append(t_list *list, char *data, t_token_type type)
{
	t_node	*temp_node;
	t_node	*new_node;

	new_node = create_node(data, type);
	if (list->head == NULL)
		list->head = new_node;
	else
	{
		temp_node = list->head;
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}
}

void	print_list(t_list *list)
{
	t_node	*current_node;

	current_node = list->head;
	while (current_node != NULL)
	{
		printf("token: %s\t\ttype: %d\n", current_node->data,
			current_node->type);
		current_node = current_node->next;
	}
}

