/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:14:05 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/14 16:50:19 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (new);
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
	while (current_node !=  NULL)
	{
		printf("token : %s\ttype : %d\n", current_node->data, current_node->type);
		current_node = current_node->next;
	}
}
