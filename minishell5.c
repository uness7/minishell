/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:41 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 13:33:48 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_awk(t_stock *stock, char **av)
{
	int		i;
	char	**new_args;
	char	*cmd;

	i = 0;
	new_args = arena_alloc(stock->arena, sizeof(char *) * 10);
	while (*av)
	{
		if (ft_strstr(*av, "\'"))
			new_args[i++] = ft_strdup(stock->arena, trim_quotes(stock->arena,
						*av));
		else
			new_args[i++] = ft_strdup(stock->arena, *av);
		av++;
	}
	if (ft_strstr(new_args[0], "/"))
		*(stock->status) = execute(stock, new_args[0], new_args);
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), new_args[0]);
		*(stock->status) = execute(stock, cmd, new_args);
	}
	return ;
}

static void	run_simple_command_helper(t_stock *stock, char **av)
{
	char	*cmd;

	if (ft_strstr(av[0], "/"))
		*(stock->status) = execute(stock, av[0], av);
	else
	{
		if (ft_strncmp(av[0], "\'", 1) == 0)
			cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
						find_paths(env_list_arr(stock->arena, stock->env,
								env_list_size(stock->env)))),
					trim_quotes(stock->arena, av[0]));
		else if (ft_strncmp(av[0], "./", 2) == 0)
			cmd = ft_strdup(stock->arena, av[0]);
		else
			cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
						find_paths(env_list_arr(stock->arena, stock->env,
								env_list_size(stock->env)))),
					trim_quotes(stock->arena, av[0]));
		*(stock->status) = execute(stock, cmd, av);
	}
}

void	run_simple_command(t_stock *stock, t_ast_node *tree, char *input)
{
	char	**av;

	av = build_command(stock->arena, tree);
	signal(SIGINT, handle_sig2);
	signal(SIGQUIT, handle_sig);
	if (strstr(av[0], "expr"))
		*(stock->status) = run_expr(stock, av, input);
	else if (ft_strcmp(av[0], "awk") == 0)
		run_awk(stock, av);
	else
		run_simple_command_helper(stock, av);
}

void	expand_env_var_in_pipes(t_cmd **commands, t_stock *stock)
{
	t_env	*var;
	char	**av;
	char	*to_find;
	t_cmd	**temp;

	temp = commands;
	while (*temp)
	{
		av = (*temp)->av;
		if (ft_strncmp(av[0], "$", 1) == 0)
		{
			to_find = av[0];
			to_find++;
			var = find_env_var(&(stock->env), to_find);
			if (var != NULL)
				(*temp)->av[0] = var->value;
		}
		temp++;
	}
}

void	expand_env_var_heredoc(t_redir_heredoc *rh, t_stock *stock)
{
	t_env	*var;
	char	**av;
	char	*to_find;

	av = rh->av;
	if (ft_strncmp(*av, "$", 1) == 0)
	{
		to_find = av[0];
		to_find++;
		var = find_env_var(&(stock->env), to_find);
		if (var != NULL)
			rh->av[0] = var->value;
	}
}
