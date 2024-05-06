/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:30 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 14:35:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_expr_helper(t_stock *stock, char **args)
{
	char	*path;

	if (ft_strstr(args[0], "/"))
		*(stock->status) = execute(stock, args[0], args);
	else
	{
		path = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))),
				trim_quotes(stock->arena, args[0]));
		*(stock->status) = execute(stock, path, args);
	}
	return (WEXITSTATUS(*(stock->status)));
}

int	run_expr(t_stock *stock, char **av, char *input)
{
	int		i;
	t_env	*env_var;
	char	**args;

	(void)av;
	i = 0;
	args = ft_split(stock->arena, input, ' ');
	while (args[++i])
	{
		if (ft_strcmp(args[i], "$?") == 0)
		{
			env_var = find_env_var(&(stock->env), "?");
			args[i] = env_var->value;
		}
	}
	return (run_expr_helper(stock, args));
}

void	update_var(t_arena *arena, t_env **env, char *input)
{
	char	*name;
	char	*value;

	input++;
	name = ft_strtok_2(input, "=");
	value = ft_strtok_2(NULL, "=");
	if (name != NULL && value != NULL)
		add_or_update_env(arena, env, name, value);
	return ;
}

void	expand_var(t_stock *stock, char *input)
{
	char		**args;
	char		*env_var;
	t_env		*var;
	t_ast_node	*tree;

	if (ft_strncmp(input, "$", 1) == 0 && strstr(input, "="))
		update_var(stock->arena, &stock->env, input);
	else
	{
		args = ft_split(stock->arena, input, ' ');
		env_var = *args;
		env_var++;
		var = find_env_var(&stock->env, env_var);
		if (var != NULL)
		{
			tree = parse(stock->arena, tokenize(stock->arena,
						trim_quotes(stock->arena, trim_space(var->value))));
			run_simple_command(stock, tree, input);
		}
	}
}

void	heredoc(t_arena *arena, char *input)
{
	char	**args;
	char	*rd;

	args = ft_split(arena, input, ' ');
	signal(SIGINT, handle_sig_heredoc);
	rd = readline("> ");
	if (!rd)
	{
		free(rd);
		free_arena(arena);
		exit(127);
	}
	free(rd);
}
