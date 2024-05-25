/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:38:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 13:03:38 by yzioual          ###   ########.fr       */
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

int	export_helper(t_stock *stock, char **args, int i)
{
	int		err_flag;
	char	*name;
	char	*value;

	value = NULL;
	err_flag = 0;
	while (args[i])
	{
		if (!ft_strstr(args[i], "="))
		{
			name = args[i];
			if (ft_isdigit(name[0]) || !check_env_var_rules(name))
			{
				dprintf(2, " not a valid identifier\n");
				err_flag = 1;
			}
			else
				add_or_update_env(stock->env_arena, &(stock->env), name, "");
		}
		else
			err_flag = export_helper_2(stock, args[i], name, value);
		i++;
	}
	return (err_flag);
}
