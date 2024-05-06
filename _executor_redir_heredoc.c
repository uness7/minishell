/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _executor_redir_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:24:19 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/03 16:01:09 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_input(char **input, int fd_out)
{
	while (*input)
	{
		write(fd_out, *input, ft_strlen(*input));
		write(fd_out, "\n", 1);
		input++;
	}
	close(fd_out);
}

static char	*find_path(t_stock *stock, t_cmd *cmd)
{
	char	**env;
	char	*res;

	env = env_list_arr(stock->arena, stock->env, env_list_size(stock->env));
	res = find_cmd(stock->arena, ft_strtok(stock->arena, find_paths(env)),
			cmd->av[0]);
	return (res);
}

int	_execute_redir_heredoc(t_stock *stock, int fd[2], t_cmd *cmd)
{
	char	**input;
	char	*path;
	pid_t	id;
	int		status;

	init_signal();
	status = 0;
	input = get_input(stock->arena, cmd->delimeter);
	path = find_path(stock, cmd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		write_input(input, fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execve(path, cmd->av, stock->envp);
		execve_err(stock->arena, stock->env);
	}
	return (status);
}
