/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 13:09:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_status = 0;

/*
   if (has_single_unclosed_quotes(input))
   heredoc_cmd(input, "\'");
   else if (has_double_unclosed_quotes(input))
   heredoc_cmd(input, "\"");
   else if (ends_with_pipe(input))
   heredoc_cmd2(input);
   */

static void	check_unclosed_quotes_or_pipe(char *input)
{
	if (has_single_unclosed_quotes(input) || has_double_unclosed_quotes(input)
		|| ends_with_pipe(input))
	{
		if (ends_with_pipe(input))
			heredoc_cmd2(input);
	}
}

static void	ign_cmd(t_program ***programs)
{
	int		i;
	int		j;

	i = 0;
	while ((*programs)[i] != NULL)
	{
		if ((*programs)[i]->cmd == NULL)
		{
			j = i;
			while ((*programs)[j] != NULL)
			{
				(*programs)[j] = (*programs)[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}


static void	run_minishell2(t_stock *stock, char *input)
{
	char		**new_envp;
	t_program	**programs;
	t_ast_node	*tree;
	t_list		*list;

	if (g_status != 0)
		*(stock->status) = g_status;
	g_status = 0;
	input = expand_variables(stock, input);
	if (ft_strlen(trim_quotes(stock->arena, trim_space(input))) == 0)
		return ;
	check_unclosed_quotes_or_pipe(input);
	list = tokenize(stock->arena, trim_quotes(stock->arena, trim_space(input)));
	if (is_input_valid(list))
	{
		tree = parse(stock->arena, list);
		programs = extract_programs(stock->arena, tree, 2 * ft_strlen(input));
		ign_cmd(&programs);
		new_envp = env_list_arr(stock->arena, stock->env,
				env_list_size(stock->env));
		if (programs != NULL)
			*(stock->status) = run_programs(programs, new_envp, stock, input);
		if (g_status != 0)
			*(stock->status) = g_status;
	}
}

static void	run_minishell(t_stock *stock)
{
	char	*input;

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
			run_minishell2(stock, input);
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
