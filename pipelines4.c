/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:11:43 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/19 11:15:41 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_subcommand_simple(t_arena *arena, t_ast_node *node,
		t_cmd ***commands, int *num_commands)
{
	(*commands)[*num_commands]->type = SIMPLE;
	(*commands)[*num_commands]->av = build_command(arena, node);
	(*commands)[*num_commands]->target = NULL;
	(*commands)[*num_commands]->delimeter = NULL;
	(*num_commands)++;
}

void	extract_subcommand_r_out(t_arena *arena, t_ast_node *node,
		t_cmd ***commands, int *num_commands)
{
	(*commands)[*num_commands]->type = R_OUT;
	(*commands)[*num_commands]->av = build_command(arena, node->right);
	(*commands)[*num_commands]->target = ft_strdup(arena, node->left->data);
	(*commands)[*num_commands]->delimeter = NULL;
	(*num_commands)++;
}

void	extract_subcommand_r_in(t_arena *arena, t_ast_node *node,
		t_cmd ***commands, int *num_commands)
{
	(*commands)[*num_commands]->type = R_IN;
	(*commands)[*num_commands]->av = build_command(arena, node->right);
	(*commands)[*num_commands]->target = ft_strdup(arena, node->left->data);
	(*commands)[*num_commands]->delimeter = NULL;
	(*num_commands)++;
}

void	extract_subcommand_r_append(t_arena *arena, t_ast_node *node,
		t_cmd ***commands, int *num_commands)
{
	(*commands)[*num_commands]->type = R_APPEND;
	(*commands)[*num_commands]->av = build_command(arena, node->right);
	(*commands)[*num_commands]->target = ft_strdup(arena, node->left->data);
	(*commands)[*num_commands]->delimeter = NULL;
	(*num_commands)++;
}

void	extract_subcommand_r_heredoc(t_arena *arena, t_ast_node *node,
		t_cmd ***commands, int *num_commands)
{
	(*commands)[*num_commands]->type = R_HEREDOC;
	(*commands)[*num_commands]->av = build_command(arena, node->right);
	(*commands)[*num_commands]->delimeter = ft_strdup(arena, node->left->data);
	(*commands)[*num_commands]->target = NULL;
	(*num_commands)++;
}
