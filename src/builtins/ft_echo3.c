/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 18:10:09 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_memory_echo(t_arena *arena)
{
	char	**result;

	result = arena_alloc(arena, sizeof(char *) * 100);
	if (result == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	return (result);
}

char	**convert_list_array(t_arena *arena, t_list *list)
{
	int		i;
	char	**args;

	i = 0;
	args = allocate_memory_echo(arena);
	while (list->head != NULL)
	{
		args[i++] = ft_strdup(arena, list->head->data);
		list->head = list->head->next;
	}
	args[i] = NULL;
	return (args);
}

void	handle_n_arg(char *args)
{
	char	*temp;
	int		i;
	int		skip_flag;

	temp = args;
	i = 0;
	skip_flag = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] != 'n')
		{
			skip_flag = 1;
			break ;
		}
		i++;
	}
	if (skip_flag == 1)
		printf("%s ", args);
}

void	check_n_arg(int *n_flag, char **args)
{
	char	*temp;
	int		i;

	temp = *args;
	if (temp && temp[0] && temp[0] == '-')
	{
		temp = args[0];
		i = 1;
		while (temp[i] != '\0')
		{
			if (temp[i] != 'n')
				break ;
			i++;
		}
		if (temp[i] == '\0')
			*n_flag = 1;
	}
}

void	search_value(char **envp_cp, char **arg)
{
	char	*value;

	value = NULL;
	while (*envp_cp)
	{
		if (ft_strncmp(*envp_cp, *arg + 1, ft_strlen(*arg + 1)) == 0)
		{
			value = ft_strchr(*envp_cp, '=') + 1;
			printf("%s ", value);
			break ;
		}
		envp_cp++;
	}
}
