/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redir_heredoc3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 22:11:03 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_run_redir_out_command2(t_stock *stock, t_redir_cmd *redir, char *cmd)
{
	if (ft_strstr(redir->av[0], "/"))
	{
		*(stock->status) = execute_redir_out(stock, redir->av[0], redir->target,
				redir->av);
	}
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), redir->av[0]);
		*(stock->status) = execute_redir_out(stock, cmd, redir->target,
				redir->av);
	}
}

static void	execute_redir_out_command(t_stock *stock, t_redir_cmd *redir,
		char **targets, char **new_args)
{
	int		fd;
	int		count;
	char	*true_target;
	char	*cmd;

	count = 0;
	while (targets[count])
	{
		fd = open(targets[count], O_RDONLY | O_CREAT, 0644);
		close(fd);
		count++;
	}
	true_target = targets[count - 1];
	if (ft_strncmp(redir->av[0], "/", 1) == 0)
	{
		*(stock->status) = execute_redir_out(stock, redir->av[0], true_target,
				new_args);
	}
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), redir->av[0]);
		*(stock->status) = execute_redir_out(stock, cmd, true_target, new_args);
	}
}

void	_run_redir_out_command(t_stock *stock, t_redir_cmd *redir, char *input)
{
	int		i;
	int		j;
	char	**targets;
	char	**new_args;
	char	**av;

	targets = extract_files(stock->arena, input);
	av = redir->av;
	i = 1;
	j = 1;
	new_args = arena_alloc(stock->arena, sizeof(char *) * ARGS);
	new_args[0] = ft_strdup(stock->arena, redir->av[0]);
	av++;
	while (*av)
	{
		if (ft_strncmp(*av, "-", 1) == 0)
			new_args[j++] = ft_strdup(stock->arena, *av);
		av++;
	}
	execute_redir_out_command(stock, redir, targets, new_args);
}
