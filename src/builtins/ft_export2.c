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
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (ft_strcmp(env[j], env[j + 1]) > 0) {
				swap_env(&env[j], &env[j + 1]);
			}
		}
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

static int	export_helper(t_stock *stock, char **args, int i)
{
	char	*value;
	char	*name;

	while (args[++i])
	{
		if (ft_strstr(args[i], "="))
		{
			name = ft_strtok_2(args[i], "=");
			if (name == NULL)
				return (1);
			if (ft_isdigit(name[0]) || !check_env_var_rules(name))
				return (1);
			value = ft_strtok_2(NULL, "=");
			if (value == NULL)
				value = ft_strdup(stock->arena, "(null)");
			if (ft_strncmp(value, "\"", 1) != 0 && ft_strncmp(value, "\'",
					1) != 0)
				value = ft_strtok_2(value, " ");
			else
				++value;
			if (value != NULL && name != NULL)
				add_or_update_env(stock->env_arena, &(stock->env), name, value);
		}
	}
	return (0);
}

int	custom_export(t_stock *stock, char *input)
{
	int		i;
	char	**args;
	char	*cmd;
	char	*var;
	char	**env;

	i = -1;
	(void)cmd;
	cmd = ft_strtok_2(input, " \t\n");
	var = ft_strtok_2(NULL, "\t\n");
	if (var == NULL)
	{
		env = env_list_arr(stock->env_arena, stock->env, env_list_size(stock->env));
		bubble_sort_arr(env);
		while (*env)
			printf("%s\n", *env++);
	}
	else
	{
		args = ft_split_2(stock->arena, var);
		if (args == NULL)
			return (0);
		if (export_helper(stock, args, i) == 1)
		{
			printf("bash: export: `%s': not a valid identifier\n", *args);
			return (1);
		}
	}
	return (0);
}
