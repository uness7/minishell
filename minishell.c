/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 15:53:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_status = 0;

static int	check_unclosed_quotes_or_pipe(t_arena *arena, char *input)
{
	(void)arena;
	if (has_single_unclosed_quotes(input) || has_double_unclosed_quotes(input)
		|| ends_with_pipe(input))
	{
		if (has_single_unclosed_quotes(input)
			|| has_double_unclosed_quotes(input))
		{
			printf("A missing single or double quote :(\n");
			return (-1);
		}
	}
	return (0);
}

static void	ign_cmd(t_program ***programs)
{
	int	i;
	int	j;

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

int	special_strlen(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

size_t	list_size(t_list *list)
{
	size_t	size;
	t_node *current;
	
	size = 0;
	current = list->head;

	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
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
	if (check_unclosed_quotes_or_pipe(stock->arena, input) == -1)
	{
		*(stock->status) = 1;
		return ;
	}
	list = tokenize(stock->arena, trim_quotes(stock->arena, trim_space(input)));
	if (list_size(list) == 0)
	{
		printf("Command not found\n");
		*(stock->status) = 127;
		return ;
	}
	if (!is_input_valid(list))
	{
		printf("Input is not valid\n");
		*(stock->status) = 1;
		return ;
	}
	tree = parse(stock->arena, list);
	if (!is_tree_valid(tree))
	{
		printf("Input is not valid\n");
		*(stock->status) = 1;
		return ;
	}
	programs = extract_programs(stock, tree, 2 * ft_strlen(input));
	if (programs == NULL)
	{
		*(stock->status) = 1;
		return ;
	}
	ign_cmd(&programs);
	new_envp = env_list_arr(stock->arena, stock->env,
			env_list_size(stock->env));
	if (programs != NULL)
		*(stock->status) = run_programs(programs, new_envp, stock);
	if (g_status != 0)
		*(stock->status) = g_status;
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
