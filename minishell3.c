/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:59:22 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 13:47:50 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_isbuiltin(t_arena *arena, char *input)
{
	char	**args;
	int		i;
	bool	is_builtin;

	i = 0;
	is_builtin = false;
	args = ft_split(arena, input, ' ');
	while (args[i])
	{
		args[i] = trim_quotes(arena, args[i]);
		i++;
	}
	if (ft_strcmp(args[0], "unset") == 0 || ft_strcmp(args[0], "pwd") == 0
		|| ft_strcmp(args[0], "exit") == 0 || ft_strcmp(args[0], "cd") == 0
		|| ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "export") == 0
		|| ft_strcmp(args[0], "env") == 0)
		is_builtin = true;
	return (is_builtin);
}

static char	*produce_input(t_arena *arena, char *input)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(arena, input, ' ');
	while (args[i])
	{
		args[i] = trim_quotes(arena, args[i]);
		i++;
	}
	return (join_args(arena, args));
}

void	_runbuiltins(t_arena *arena, char *input, t_env *env, int *status)
{
	input = produce_input(arena, input);
	if (ft_strncmp(trim_quotes(arena, input), "pwd", 3) == 0)
		ft_pwd(arena);
	else if (ft_strncmp("env", trim_quotes(arena, input), 3) == 0)
		print_env(env);
	else if (ft_strncmp(trim_quotes(arena, input), "exit", 4) == 0)
		ft_exit(arena, input, status);
	else if (ft_strncmp(trim_quotes(arena, input), "cd", 2) == 0)
	{
		if (ft_strncmp(input, "cd..", 4) == 0)
			return ;
		custom_cd(arena, trim_quotes(arena, input), env);
	}
	else if (ft_strncmp(trim_quotes(arena, input), "export",
			ft_strlen("export")) == 0)
		custom_export(arena, input, env);
	else if (ft_strncmp(trim_quotes(arena, input), "unset",
			ft_strlen("unset")) == 0)
		custom_unset(trim_quotes(arena, input), env);
	else if (ft_strncmp(trim_quotes(arena, input), "echo",
			ft_strlen("echo")) == 0)
		custom_echo(arena, trim_quotes(arena, input), env);
	add_or_update_env(arena, &env, "?", ft_itoa(arena, *status));
}

char	*join_args(t_arena *arena, char **args)
{
	char	*input;
	size_t	total_length;
	size_t	i;

	total_length = 0;
	i = 0;
	while (args[i])
	{
		total_length += ft_strlen(args[i]);
		if (args[i + 1] != NULL)
			total_length++;
		i++;
	}
	input = arena_alloc(arena, total_length + 1);
	input[0] = '\0';
	while (*args)
	{
		ft_strcat(input, *args);
		if (*(args + 1) != NULL)
			ft_strcat(input, " ");
		args++;
	}
	return (input);
}

void	run_pipeline_command(t_stock *stock, t_ast_node *tree)
{
	t_cmd	**commands;
	int		num_commands;
	int		i;
	int		fd;

	commands = NULL;
	i = 0;
	fd = -1;
	num_commands = 0;
	extract_commands(stock->arena, tree, &commands, &num_commands);
	commands[num_commands] = NULL;
	inverse_commands_order(stock->arena, commands);
	expand_env_var_in_pipes(commands, stock);
	*(stock->status) = execute_pipeline(stock, commands, &i, &fd);
}
