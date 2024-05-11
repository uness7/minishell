/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:30:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/11 12:44:31 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_heredoc(int a)
{
	(void)a;
	printf("\n");
	exit(0);
}

char	**extract_input(char *last_deli)
{
	pid_t	id;
	int		i;
	char	**input;
	char	*buffer;

	input = malloc(sizeof(char *) * (100));
	i = 0;
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (!id)
	{
		signal(SIGINT, quit_heredoc);
		while (1)
		{
			buffer = readline("> ");
			if (buffer == NULL || ft_strcmp(last_deli, buffer) == 0)
			{
				free(buffer);
				break ;
			}
			input[i++] = strdup(buffer);
			free(buffer);
		}
		input[i] = NULL;
		exit(1);
	}
	int status = 0;
	waitpid(id, &status, 0);
	return (input);
}


void	run_redir_heredoc_command(t_stock *stock, t_ast_node *tree)

{
	int count_deli;
	int count_arg;
	int i;
	int j;
	int k;
	int no_cmd_flag;
	t_redir_heredoc *rh;
	t_hd_arr **av;
	char **delimiters;
	char **args;
	char *cmd;
	char *last_deli;
	char *second_last_deli;

	last_deli = NULL;
	second_last_deli = NULL;
	no_cmd_flag = 0;
	i = 0;
	j = 0;
	k = 0;
	count_deli = 0;
	count_arg = 0;
	rh = build_cmd_redir_heredoc(stock->arena, tree);
	av = rh->av;
	while (av[i])
	{
		if (av[i]->type == DELI)
			count_deli++;
		else if (av[i]->type == ARG)
			count_arg++;
		else if (av[i]->type == NO_CMD)
			no_cmd_flag = 1;
		i++;
	}

	delimiters = arena_alloc(stock->arena, sizeof(char *) * (count_deli + 1));
	args = arena_alloc(stock->arena, sizeof(char *) * (count_arg + 1));

	i = 0;
	cmd = NULL;
	k = 0;
	while (av[i])
	{
		if (av[i]->type == DELI)
			delimiters[j++] = ft_strdup(stock->arena, av[i]->data);
		else if (av[i]->type == ARG)
			args[k++] = ft_strdup(stock->arena, av[i]->data);
		else if (av[i]->type == CMD)
			cmd = ft_strdup(stock->arena, av[i]->data);
		i++;
	}

	last_deli = ft_strdup(stock->arena, delimiters[0]);
	if (delimiters[1] != NULL)
		second_last_deli = ft_strdup(stock->arena, delimiters[1]);

	/*
		* We have access to :
		* 	- cmd : cat, sort , grep 
		* 	- args: grep 'pattern' 
		* 	- last deli : d2
		* 	- second last deli : d1
		* */

	char	**input = extract_input(last_deli);
	char *av2[] = {"/usr/bin/sort", NULL};
	execute_redir_heredoc(stock, "/usr/bin/sort", input, av2);
}


