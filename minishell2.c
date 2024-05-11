/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:17:38 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/11 12:30:42 by yzioual          ###   ########.fr       */
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
