/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/22 14:56:17 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_status = 0;

static void	run_minishell2(t_stock *stock, char *input, char **new_envp)
{
	t_program	**programs;
	t_ast_node	*tree;
	t_list		*list;

	update_status(stock);
	g_status = 0;
	input = expand_variables(stock, input);
	if (check_unclosed_quotes_or_pipe(stock->arena, input) == -1)
		return (err_message(stock, 1));
	list = tokenize(stock->arena, trim_space(input));
	if (list_size(list) == 0)
		return (err_message(stock, 127));
	if (!is_input_valid(list))
		return (err_message(stock, 1));
	tree = parse(stock->arena, list);
	if (!is_tree_valid(tree))
		return (err_message(stock, 1));
	programs = extract_programs(stock, tree, 2 * ft_strlen(input));
	if (programs == NULL)
		return (err_message(stock, 1));
	ign_cmd(&programs);
	*(stock->status) = run_programs(programs, new_envp, stock);
	update_status(stock);
}

static void	run_minishell(t_stock *stock)
{
	char	*input;
	char	**new_envp;

	new_envp = env_list_arr(stock->arena, stock->env,
			env_list_size(stock->env));
	while (1)
	{
		init_signal();
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;35m~> %  \033[0m ");
		if (!input)
		{
			printf("exit\n");
			free_arena(stock->arena);
			break ;
		}
		if (*input)
			add_history(input);
		if (input[0] != '\0')
			run_minishell2(stock, input, new_envp);
		free(input);
		g_status = 0;
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_stock	stock;
	t_arena	arena;
	t_env	*env;
	char	**envp_cp;
	int		status;

	status = 0;
	arena_init(&arena, ARENA_SIZE);
	if (ac > 1)
	{
		printf("Minishell dosen't take any arguments\n");
		return (0);
	}
	stock.argv = argv;
	stock.envp = envp;
	envp_cp = envp;
	env = ft_env(&arena, envp_cp);
	stock.env = env;
	stock.arena = &arena;
	stock.status = &status;
	run_minishell(&stock);
	return (0);
}
