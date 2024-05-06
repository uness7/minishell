/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:20:48 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/19 10:59:38 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dispenser(t_arena *arena, t_ast_node *node, t_cmd ***commands,
		int *num_commands)
{
	if (node->type == NODE_COMMAND)
		extract_subcommand_simple(arena, node, commands, num_commands);
	else if (node->type == NODE_REDIRECTION_OUT)
		extract_subcommand_r_out(arena, node, commands, num_commands);
	else if (node->type == NODE_REDIRECTION_IN)
		extract_subcommand_r_in(arena, node, commands, num_commands);
	else if (node->type == NODE_REDIRECTION_APPEND)
		extract_subcommand_r_append(arena, node, commands, num_commands);
	else if (node->type == NODE_REDIRECTION_HEREDOC)
		extract_subcommand_r_heredoc(arena, node, commands, num_commands);
}

void	extract_commands(t_arena *arena, t_ast_node *node, t_cmd ***commands,
		int *num_commands)
{
	t_cmd	**new_commands;
	int		i;

	if (node == NULL)
		return ;
	if (node->type == NODE_PIPELINE)
	{
		extract_commands(arena, node->left, commands, num_commands);
		extract_commands(arena, node->right, commands, num_commands);
	}
	else
	{
		new_commands = arena_alloc(arena, (*num_commands + 1)
				* sizeof(t_cmd *));
		if (new_commands == NULL)
			return ;
		i = -1;
		while (++i < *num_commands)
			new_commands[i] = (*commands)[i];
		*commands = new_commands;
		(*commands)[*num_commands] = arena_alloc(arena, sizeof(t_cmd));
		if ((*commands)[*num_commands] == NULL)
			return ;
		dispenser(arena, node, commands, num_commands);
	}
}

void	inverse_commands_order(t_arena *arena, t_cmd **cmds)
{
	int		num_cmds;
	int		i;
	t_cmd	**reversed_cmds;

	num_cmds = 0;
	while (cmds[num_cmds] != NULL)
		num_cmds++;
	reversed_cmds = arena_alloc(arena, (num_cmds + 1) * sizeof(t_cmd *));
	if (reversed_cmds == NULL)
	{
		printf("Memory allocation failed\n");
		return ;
	}
	i = -1;
	while (++i < num_cmds)
		reversed_cmds[num_cmds - i - 1] = cmds[i];
	reversed_cmds[num_cmds] = NULL;
	i = -1;
	while (++i < num_cmds)
		cmds[i] = reversed_cmds[i];
	cmds[num_cmds] = NULL;
}
