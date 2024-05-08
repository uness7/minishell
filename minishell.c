/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/08 18:06:19 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dispenser(t_ast_node *tree, t_stock *stock, char *input)
{
	if (tree != NULL)
	{
		if (tree->type == NODE_COMMAND && _isbuiltin(stock->arena, input))
			_runbuiltins(stock, input);
		else if (tree->type == NODE_COMMAND)
			run_simple_command(stock, tree, input);
		else if (tree->type == NODE_REDIRECTION_OUT)
			run_redir_out_command(stock, input, tree);
		else if (tree->type == NODE_REDIRECTION_APPEND)
			run_redir_append_command(stock, input, tree);
		else if (tree->type == NODE_REDIRECTION_HEREDOC)
			run_redir_heredoc_command(stock, input, tree);
		else if (tree->type == NODE_REDIRECTION_IN)
			run_redir_in_command(stock, tree);
		else if (tree->type == NODE_PIPELINE)
			run_pipeline_command(stock, tree);
	}
}

static void	cmd_not_found(t_stock *stock)
{
	ft_putstr_fd("Command Not Found\n", 1);
	*(stock->status) = 127;
	add_or_update_env(stock->arena, &(stock->env), "?", ft_itoa(stock->arena,
			*(stock->status)));
}

static void	run_minishell2(t_stock *stock, char *input)
{
	t_ast_node	*tree;
	t_list		*list;

	input = expand_variables(stock, input);
	list = tokenize(stock->arena, trim_quotes(stock->arena, trim_space(input)));
	tree = parse(stock->arena, list);

	if (is_input_valid2(trim_space(input)) && \
			is_input_valid(trim_space(input)) && \
			check_invalid_combinations(stock->arena, list, stock->env))
	{
		signal(SIGINT, handle_sig2);
		if (tree != NULL)
			dispenser(tree, stock, input);
		add_or_update_env(stock->arena, &(stock->env), "?",
				ft_itoa(stock->arena, *(stock->status)));
	}
	else
		cmd_not_found(stock);
}

static void	run_minishell(t_stock *stock)
{
	char	*input;

	while (1)
	{
		init_signal();
		input = readline("\033[0;35mninjashell 🥷 > \033[0m ");
		if (!input)
		{
			printf("exit\n");
			free_arena(stock->arena);
			break ;
		}
		if (*input)
			add_history(input);
		if (input[0] != '\0')
			run_minishell2(stock, input);
		free(input);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_stock	stock;
	t_arena	arena;
	t_env	*env;
	char	**envp_cp;
	int		status;

	arena_init(&arena, ARENA_SIZE);
	if (ac > 1)
	{
		printf("Minishell dosen't take any arguments\n");
		return (0);
	}
	status = 0;
	stock.argv = argv;
	stock.envp = envp;
	envp_cp = envp;
	env = ft_env(&arena, envp_cp);
	stock.env = env;
	stock.arena = &arena;
	stock.status = &status;
	add_or_update_env(&arena, &env, "?", ft_itoa(&arena, status));
	run_minishell(&stock);
	return (0);
}
