/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/13 20:19:50 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PROTOTYPES */
void	reverse_programs(t_program **programs);
void    print_programs(t_program **programs);
void print_program(char **args);

static void	run_minishell2(t_stock *stock, char *input)
{
	t_program	**programs;
	t_ast_node	*tree;
	t_list		*list;

	input = expand_variables(stock, input);
	list = tokenize(stock->arena, trim_quotes(stock->arena, trim_space(input)));
//	if (is_input_valid(input) && is_input_valid2(input) && check_invalid_combinations(stock->arena, list, stock->env))
//	{
		tree = parse(stock->arena, list);
		//(void)programs;
		//print_tree(tree);
		programs = extract_programs(tree, 2 * strlen(input));	
		//reverse_programs(programs);
		//print_programs(programs);
		int status = run_programs(programs, stock->envp, stock, input);
		add_or_update_env(stock->arena, &(stock->env), "?", ft_itoa(stock->arena, status));
//	}
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
