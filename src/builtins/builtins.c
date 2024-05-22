/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:29:59 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 13:51:12 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **arr)
{
	int	size;

	size = 0;
	while (arr[size] != NULL)
		size++;
	return (size);
}

void	custom_unset(t_stock *stock, char *input, t_env *env)
{
	char	**args;

	input += 5;
	args = ft_split(stock->arena, input, ' ');
	if (array_size(args) != 0)
	{
		while (*args != NULL)
		{
			unset(&env, *args);
			args++;
		}
	}
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
