/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:38:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/30 17:48:40 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_cd(t_arena *arena, char *input, t_env *env)
{
	char	*cmd;
	char	*path;
	char	**args;
	int		i;

	i = 0;
	args = ft_split(arena, input, ' ');
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("too many arguments :( \n");
		return ;
	}
	cmd = ft_strtok_2(input, " \t\n");
	path = ft_strtok_2(NULL, " \t\n");
	(void)cmd;
	ft_cd(arena, path, env);
}

void	custom_export(t_stock *stock, char *input)
{
	char	*cmd;
	char	*var;
	char	*value;
	char	*name;
	char	**args;

	(void)cmd;
	cmd = ft_strtok_2(input, " \t\n");
	var = ft_strtok_2(NULL, "\t\n");
	args = convert_list_array(stock->arena, tokenize(stock->arena, var));
	if (args != NULL)
	{
		while (*args)
		{
			if (strstr(*args, "="))
			{
				name = ft_strtok_2(*args, "=");
				value = ft_strtok_2(NULL, "=");
				if (ft_strncmp(value, "\"", 1) != 0)
					value = ft_strtok_2(value, " ");
				if (value != NULL && name != NULL)
					add_or_update_env(stock->arena, &(stock->env), \
							name, trim_quotes(stock->arena, value));
			}
			args++;
		}
	}
	else
		print_env(stock->env);
}
