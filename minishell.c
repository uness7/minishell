/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/15 20:40:31 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	reverse_programs(t_program **programs);
void    print_programs(t_program **programs);
void print_program(char **args);

static void	run_minishell2(t_stock *stock, char *input)
{
	char		**new_envp;
	int		status = 0;
	t_program	**programs;
	t_ast_node	*tree;
	t_list		*list;

	new_envp = NULL;
	if (g_status != 0)
		*(stock->status) = g_status;
	g_status = 0;
	input = expand_variables(stock, input);
	list = tokenize(stock->arena, trim_quotes(stock->arena, trim_space(input)));
/*	if (ends_with_pipe(stock->arena, input) || !is_input_valid2(input))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	*/
	if (check_invalid_combinations(stock->arena, list, stock->env))
	{
		tree = parse(stock->arena, list);
		if (!is_input_valid(input))
			extract_program_heredoc(tree, 1);
		programs = extract_programs(tree, 2 * strlen(input));	
		print_tree(tree);
		printf("\n\n");
		print_programs(programs);
		exit(0);
		new_envp = env_list_arr(stock->arena, \
				stock->env, env_list_size(stock->env));
		if (programs != NULL)
			status = run_programs(programs, new_envp, stock, input);
		*(stock->status) = status;
		if (g_status != 0)
			*(stock->status) = g_status;
	}
}

void print_program(char **args)
{
	if (args == NULL) {
		printf("Arguments: None\n");
		return;
	}
	printf("Arguments:\n");
	for (int i = 0; args[i] != NULL; i++) {
		printf("  [%d]: %s\n", i, args[i]);
	}
}

void	print_programs(t_program **programs)
{
	if (programs == NULL) {
		printf("No programs to display.\n");
		return;
	}

	int index = 0;
	while (programs[index] != NULL) {
		t_program *p = programs[index];
		printf("Program %d:\n", index);
		printf("  Command: %s\n", p->cmd ? p->cmd : "None");
		print_program(p->args);
		printf("  File descriptors: in=%d, out=%d\n", p->fd_in, p->fd_out);
		printf("  Here Document Flag: %s\n", p->fd_heredoc ? "Yes" : "No");
		printf("\n");
		index++;
	}
}


void	reverse_programs(t_program **programs)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	if (!programs)
		return ;
	while (programs[length])
		length++;
	while (i < length / 2)
	{
		t_program *temp = programs[i];
		programs[i] = programs[length - i - 1];
		programs[length - i - 1] = temp;
		i++;
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
	int	status = 0;

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
