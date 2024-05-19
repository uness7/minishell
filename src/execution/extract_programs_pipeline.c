/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_programs_pipeline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:49:46 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 17:15:27 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_programs_pipeline_helper_r(t_arena \
		*arena, t_ast_node *root, int *i, t_program **programs)
{
	if (root->right->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(arena, root->right);
	else if (root->right->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(arena, root->right);
	else if (root->right->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(arena, \
				root->right, 1);
	else if (root->right->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(arena, \
				root->right, 0);
	else if (root->right->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(arena, root->right, 0);
}

t_program	**extract_programs_pipeline(t_arena *arena, t_ast_node *root, t_program **programs, int programs_count, int *i)
{
	if (programs == NULL)
		programs = arena_alloc(arena, \
				sizeof(t_program *) * (2 * programs_count + 1));
	extract_programs_pipeline_helper_r(arena, root, i, programs);
	if (root->left->type == NODE_PIPELINE)
		return (extract_programs_pipeline(arena, \
				root->left, programs, programs_count, i));
	else if (root->left->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(arena, root->left);
	else if (root->left->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(arena, root->left);
	else if (root->left->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(arena, \
				root->left, 1);
	else if (root->left->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(arena, \
				root->left, 0);
	else if (root->left->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(arena, root->left, 0);
	programs[*i] = NULL;
	return (programs);
}
