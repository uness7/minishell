/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redir_heredoc5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:23:45 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/06 22:53:48 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_run_redir_heredoc_command2(t_stock *stock, t_redir_heredoc *rh,
		char *cmd)
{
	char	**input;

	input = get_input(stock->arena, rh->delimeter);
	if (ft_strstr(rh->av[0], "/"))
		*(stock->status) = execute_redir_heredoc(stock, \
				rh->av[0], input, rh->av);
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), rh->av[0]);
		*(stock->status) = execute_redir_heredoc(stock, cmd, input, rh->av);
	}
	return ;
}

static void	execute_redir_heredoc_command(t_stock *stock, t_redir_heredoc *rh,
		char *true_deli, char **new_args)
{
	char	*cmd;
	char	**input;

	input = get_input(stock->arena, true_deli);
	if (ft_strstr(rh->av[0], "/"))
		*(stock->status) = execute_redir_heredoc(stock, \
				rh->av[0], input, new_args);
	else
	{
		cmd = find_cmd(stock->arena, ft_strtok(stock->arena,
					find_paths(env_list_arr(stock->arena, stock->env,
							env_list_size(stock->env)))), rh->av[0]);
		*(stock->status) = execute_redir_heredoc(stock, cmd, input, new_args);
	}
}

void	_run_redir_heredoc_command(t_stock *stock,
		t_redir_heredoc *redir_heredoc, char *input)
{
	char	**av;
	int		j;
	char	*true_deli;
	char	**delims;
	char	**new_args;

	delims = convert_list_array(stock->arena, tokenize(stock->arena, input));
	av = redir_heredoc->av;
	j = 0;
	while (*delims)
		delims++;
	true_deli = *(delims - 1);
	new_args = arena_alloc(stock->arena, sizeof(char *) * ARGS);
	while (ft_strcmp(*av, true_deli) != 0)
	{
		new_args[j++] = ft_strdup(stock->arena, *av);
		av++;
	}
	execute_redir_heredoc_command(stock, redir_heredoc, true_deli, new_args);
}
