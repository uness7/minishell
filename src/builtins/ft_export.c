/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:09:18 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 13:53:28 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env **head, char *key)
{
	t_env	*current;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_env_var(t_arena *arena, t_env *env_var, char *name, char *value)
{
	env_var->value = ft_strdup(arena, value);
	env_var->name = ft_strdup(arena, name);
}

void	add_or_update_env(t_arena *arena, t_env **head, char *name, char *value)
{
	t_env	*env_var;
	t_env	*new_node;
	t_env	*current;

	env_var = find_env_var(head, name);
	if (env_var != NULL)
		update_env_var(arena, env_var, name, value);
	else
	{
		new_node = arena_alloc(arena, sizeof(t_env));
		new_node->name = ft_strdup(arena, name);
		new_node->value = ft_strdup(arena, value);
		new_node->next = NULL;
		if (*head == NULL)
			*head = new_node;
		else
		{
			current = *head;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
	}
}

void	unset(t_env **list, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *list;
	prev = NULL;
	while (temp != NULL && name != NULL && temp->name != NULL
		&& ft_strcmp(temp->name, name) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	if (prev == NULL)
		*list = temp->next;
	else
		prev->next = temp->next;
}
