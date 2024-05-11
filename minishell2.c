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

int	heredoc(char *delim)
{
	char	buff[BUFFERSIZE + 1];

	int hfd[2], nbytes, len;
	if (pipe(hfd) == -1)
	{
		return (-1);
	}
	len = strlen(delim);
	write(1, "heredoc> ", 9);
	while ((nbytes = read(0, buff, BUFFERSIZE)) > 0)
	{
		buff[nbytes] = 0;
		if (nbytes == len + 1 && (memcmp(delim, buff, len) == 0) && buff[nbytes
			- 1] == '\n')
		{
			break ;
		}
		write(hfd[WRITE_END], buff, nbytes);
		write(1, "heredoc> ", 9);
	}
	close(hfd[WRITE_END]);
	return (hfd[READ_END]);
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
		* 	- cmd
		* 	- args
		* 	- last deli
		* */

	signal(SIGINT, handle_sig);
	int fd = heredoc(last_deli);
	char buffer[BUFFERSIZE + 1];
	char stored_data[BUFFERSIZE + 1];
	size_t total_bytes_read = 0;
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFERSIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		memcpy(stored_data + total_bytes_read, buffer, bytes_read);
		total_bytes_read += bytes_read;
	}

	stored_data[total_bytes_read] = '\0';
	close(fd);

	char *av2[] = {"/usr/bin/sort", NULL};
	execute_redir_heredoc(stock, "/usr/bin/sort", stored_data, av2);
}
