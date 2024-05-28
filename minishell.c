/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/28 00:27:27 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					g_status = 0;

static void	helper(char **av, t_stock *stock)
{
	while (*av)
	{
		if (ft_strncmp(*av, "\"", 1) == 0)
			*av = trim_quotes(stock->arena, *av);
		else if (ft_strncmp(*av, "\'", 1) == 0)
			*av = trim_single_quotes(stock->arena, *av);
		av++;
	}
}

static t_program	**produce_programs(t_program **programs, t_stock *stock)
{
	t_program	**cpy;

	cpy = programs;
	while (*programs)
	{
		if ((*programs)->cmd && ft_strncmp((*programs)->cmd, "\"", 1) == 0)
			(*programs)->cmd = trim_quotes(stock->arena, (*programs)->cmd);
		else if ((*programs)->cmd && ft_strncmp((*programs)->cmd, "\'", 1) == 0)
			(*programs)->cmd = trim_single_quotes(stock->arena,
					(*programs)->cmd);
		if ((*programs)->args != NULL)
			helper((*programs)->args, stock);
		programs++;
	}
	return (cpy);
}

char	*ign_quotes(t_arena *arena, char *s)
{
	char	*result;
	int		i;
	int		j;
	int		size;

	j = 0;
	i = 0;
	size = ft_strlen(s);
	result = arena_alloc(arena, sizeof(char) * (size + 1));
	while (s[i])
	{
		while (s[i] && (s[i] == '\'' || s[i] == '"'))
			i++;
		result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static void	run_minishell2(t_stock *stock, char *input, char **new_envp)
{
	t_program	**programs;
	t_program	**programs_cpy;
	t_ast_node	*tree;
	t_list		*list;

	update_status(stock);
	g_status = 0;
	if (check_unclosed_quotes_or_pipe(stock->arena, input) == -1)
		return (err_message(stock, 1));
	input = expand_variables(stock, input);
	list = tokenize(stock->arena, input);
	if (list_size(list) == 0)
		return (err_message(stock, 1));
	if (!is_input_valid(list))
		return (err_message(stock, 1));
	tree = parse(stock->arena, list);
	if (!is_tree_valid(tree))
		return (err_message(stock, 1));
	programs = extract_programs(stock, tree, 2 * ft_strlen(input));
	programs_cpy = produce_programs(programs, stock);
	if (programs_cpy == NULL)
		return (err_message(stock, 1));
	ign_cmd(&programs_cpy);
	*(stock->status) = run_programs(programs_cpy, new_envp, stock);
	update_status(stock);
}

static void	run_minishell(t_stock *stock, int status)
{
	char	*input;
	char	**new_envp;

	stock->status = &status;
	while (1)
	{
		arena_init(stock->arena, ARENA_SIZE);
		new_envp = env_list_arr(stock->env_arena, stock->env,
				env_list_size(stock->env));
		init_signal();
		input = readline("\033[0;35m~> %  \033[0m ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (input[0] != '\0')
			run_minishell2(stock, input, new_envp);
		free(input);
		free_arena(stock->arena);
		g_status = 0;
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_stock	stock;
	t_arena	arena;
	t_arena	env_arena;
	t_env	*env;
	char	**envp_cp;

	arena_init(&env_arena, ARENA_SIZE);
	if (ac > 1)
	{
		printf("Minishell dosen't take any arguments\n");
		return (0);
	}
	stock.argv = argv;
	stock.envp = envp;
	envp_cp = envp;
	env = ft_env(&env_arena, envp_cp);
	stock.env = env;
	stock.arena = &arena;
	stock.env_arena = &env_arena;
	stock.last_open_fd = -1;
	run_minishell(&stock, 0);
	rl_clear_history();
	free_arena(stock.arena);
	free_arena(stock.env_arena);
	return (0);
}
