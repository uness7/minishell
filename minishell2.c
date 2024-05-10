/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:17:38 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/10 19:26:59 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_redir_out_command(t_stock *stock, char *input, t_ast_node *tree)
{
	char		*cmd;
	t_redir_cmd	*redir;

	redir = build_cmd_redir_out(stock->arena, tree);
	if (redir == NULL || redir->av == NULL || redir->target == NULL)
	{
		printf("Syntax error :( \n");
		*(stock->status) = 127;
		return ;
	}
	cmd = NULL;
	if (has_multiple_redir_out(input) == true)
		_run_redir_out_command(stock, redir, input);
	else
		_run_redir_out_command2(stock, redir, cmd);
}

void	run_redir_append_command(t_stock *stock, char *input, t_ast_node *tree)
{
	char		*cmd;
	t_redir_cmd	*redir;

	redir = build_cmd_redir_append(stock->arena, tree);
	if (redir == NULL || redir->av == NULL || redir->target == NULL)
	{
		printf("Syntax error :(\n");
		*(stock->status) = 127;
		return ;
	}
	cmd = NULL;
	if (has_multiple_redir_append(input) == true)
		_run_redir_append_command(stock, redir, input);
	else
		_run_redir_append_command2(stock, redir, cmd);
}

void	run_redir_in_command(t_stock *stock, t_ast_node *tree)
{
	t_redir_cmd	*redir;
	char		*cmd;

	redir = build_cmd_redir_in(stock->arena, tree);
	if (redir == NULL || redir->av == NULL || redir->target == NULL)
	{
		printf("Syntax error :(\n");
		*(stock->status) = 127;
		return ;
	}
	cmd = NULL;
	if (ft_strstr(redir->av[0], "/"))
	{
		*(stock->status) = execute_redir_in(stock, redir->av[0], redir->target,
				redir->av);
	}
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), redir->av[0]);
		*(stock->status) = execute_redir_in(stock, cmd, redir->target,
				redir->av);
	}
}

void	quite_heredoc(int a)
{
	(void)a;
	write(1, "\n", 1);
	exit(0);
}

void	run_redir_heredoc_command(t_stock *stock, t_ast_node *tree)

{
	int		count_deli;
	int		count_arg;
	int		i;
	int		j;
	int		k;
	int		no_cmd_flag;
	t_redir_heredoc	*rh;
	t_hd_arr	**av;
	char	**delimiters;
	char	**args;
	char	*cmd;
	char	*last_deli;
	char	*second_last_deli;

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
	/*
	printf("count of deli : %d\n", count_deli);
	printf("count of args : %d\n", count_arg);
	printf("no cmd flag : %d\n", no_cmd_flag);
	*/
	delimiters = arena_alloc(stock->arena, sizeof(char *) * (count_deli + 1));
	args = arena_alloc(stock->arena, sizeof(char *) * (count_arg + 1));

	// making delimiters and args arrays
	i = 0;
	cmd = NULL;
	k = 1;
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
	args[0] = cmd;
	/*
	i = 0;
	while (delimiters[i])
	{
		printf("deli : %s\n", delimiters[i]);
		i++;
	}

	i = 0;
	while (args[i])
	{
		printf("args : %s\n", args[i]);
		i++;
	}
	
	if (no_cmd_flag == 1)
		printf("There was no command detected\n");
	else
		printf("cmd : %s\n", cmd);
		*/
	last_deli = ft_strdup(stock->arena, delimiters[0]);
	if (delimiters[1] != NULL)
		second_last_deli = ft_strdup(stock->arena, delimiters[1]);
	/*
	printf("last deli : %s\n", last_deli);
	if (second_last_deli != NULL)
		printf("second last deli : %s\n", last_deli);
		*/

	//printf("input : %s\n", input);

	pid_t	pid;
	int	status;
	int	fd[2];
	
	pipe(fd);
	pid = fork();

	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, quite_heredoc);
		char	*line = NULL;
		//char	**input = arena_alloc(arena, sizeof(char *)); 
		char	*input = "";
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				break ;
			if (ft_strcmp(line, last_deli) == 0)
			{
				free(line);
				break ;
			}
			input = ft_strjoin(stock->arena, input, line);
			input = ft_strjoin(stock->arena, input, "\n");
			free(line);
		}
		write(fd[1], input, sizeof(input));
		write(1, "\n", 1);
		exit(1);
	}
	waitpid(pid, &status, 0);
	dup2(fd[0], 0);
	execve(cmd, args, stock->envp);
}
