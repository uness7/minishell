/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:29:59 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/27 14:28:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_unset(char *input, t_env *env)
{
	char	*cmd;
	char	*var_name;

	(void)cmd;
	cmd = ft_strtok_2(input, " \t\n");
	var_name = ft_strtok_2(NULL, " \t\n");
	if (var_name == NULL)
	{
		printf("you have to specify which env variable to unset :)\n");
		return ;
	}
	unset(&env, var_name);
}

int	array_size(char **arr)
{
	int	size;

	size = 0;
	while (arr[size] != NULL)
		size++;
	return (size);
}

int	env_list_size(t_env *list)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = list;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_list_arr(t_arena *arena, t_env *temp, int size)
{
	int		i;
	char	**env_args;
	char	*input2;
	char	*p;
	size_t	len;

	len = 0;
	env_args = arena_alloc(arena, sizeof(char *) * (size + 1));
	i = 0;
	while (temp != NULL)
	{
		len = ft_strlen(temp->name) + ft_strlen(temp->value) + 2;
		input2 = arena_alloc(arena, len);
		p = input2;
		ft_strcpy(p, temp->name);
		p += ft_strlen(temp->name);
		*p++ = '=';
		ft_strcpy(p, temp->value);
		env_args[i] = ft_strdup(arena, input2);
		i++;
		temp = temp->next;
	}
	env_args[i] = NULL;
	return (env_args);
}
