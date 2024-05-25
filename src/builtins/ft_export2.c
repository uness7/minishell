/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:38:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/23 15:06:31 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env(char **a, char **b)
{
	char	*temp;

	temp = NULL;
	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort_arr(char **env)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	while (env[n])
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_env(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

bool	check_env_var_rules(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) && !ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	export_helper_2(t_stock *stock, char *word)
{
	char	*name;
	char	*value;
	int		err_flag;

	value = NULL;
	err_flag = 0;
	name = ft_strtok_2(word, "=");
	if (name == NULL)
		return (1);
	if (ft_isdigit(name[0]) || !check_env_var_rules(name))
	{
		printf("bash: export: `%s': not a valid identifier\n", word);
		err_flag = 1;
	}
	else
	{
		value = ft_strtok_2(NULL, "=");
		if (value == NULL)
			value = ft_strdup(stock->arena, "");
		if (ft_strncmp(value, "\"", 1) != 0 && ft_strncmp(value, "\'", 1) != 0)
			value = ft_strtok_2(value, " ");
		else
			++value;
		if (value != NULL && name != NULL)
			add_or_update_env(stock->env_arena, &(stock->env), name, value);
		err_flag = 0;
	}
	return (err_flag);
}

int	export_helper(t_stock *stock, char **args, int i)
{
	int		err_flag;
	char	*name;

	err_flag = 0;
	while (args[i])
	{
		if (!ft_strstr(args[i], "="))
		{
			name = args[i];
			if (ft_isdigit(name[0]) || !check_env_var_rules(name))
			{
				printf("bash: export: `%s': not a valid identifier\n", *args);
				err_flag = 1;
			}
			else
				add_or_update_env(stock->env_arena, &(stock->env), name, "");
		}
		else
			err_flag = export_helper_2(stock, args[i]);
		i++;
	}
	return (err_flag);
}
