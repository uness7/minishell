/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:09:52 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/14 17:26:26 by yzioual          ###   ########.fr       */
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
	int		i;
	t_env	*env_list;
	char	**env_copy;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
		i++;
	env_copy = arena_alloc(arena, sizeof(char *) * (i + 1));
	if (env_copy == NULL)
		return (NULL);
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(arena, env[i]);
	env_copy[i] = NULL;
	i = 0;
	env_list = NULL;
	while (env_copy[i])
	{
		name = ft_strtok_2(env_copy[i], "=");
		value = ft_strtok_2(NULL, "=");
		append_env_node(arena, &env_list, name, value);
		i++;
	}
	return (env_list);
}
