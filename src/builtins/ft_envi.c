/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:09:52 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/25 16:16:33 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(t_arena *arena, char *name, char *value)
{
	t_env	*new_node;

	new_node = arena_alloc(arena, sizeof(t_env));
	new_node->value = ft_strdup(arena, value);
	new_node->name = ft_strdup(arena, name);
	new_node->next = NULL;
	return (new_node);
}

void	append_env_node(t_arena *arena, t_env **head, char *name, char *value)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = new_env_node(arena, name, value);
	if (!(*head))
	{
		*head = new_node;
		return ;
	}
	last_node = *head;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
}

char	**ft_str_copy(t_arena *arena, char **envp)
{
	int		i;
	char	**env_copy;

	env_copy = NULL;
	i = 0;
	while (envp[i])
		i++;
	env_copy = arena_alloc(arena, sizeof(char *) * (i + 1));
	if (env_copy == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(arena, envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

t_env	*ft_env(t_arena *arena, char **env)
{
	t_env	*env_list;
	char	**env_copy;
	int		i;
	char	*name;
	char	*value;

	env_list = NULL;
	env_copy = arena_alloc(arena, sizeof(char *) * (array_size(env) + 1));
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(arena, env[i]);
	env_copy[i] = NULL;
	i = -1;
	while (env_copy[++i])
	{
		name = env_copy[i];
		value = ft_strchr(env_copy[i], '=');
		if (value)
			*value++ = '\0';
		else
			value = "";
		append_env_node(arena, &env_list, name, value);
	}
	return (env_list);
}
