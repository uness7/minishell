/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_programs_pipeline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:49:46 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 12:35:10 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_programs_pipeline_helper_r(t_stock \
		*stock, t_ast_node *root, int *i, t_program **programs)
{
	if (root->right->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(stock->arena, root->right);
	else if (root->right->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(stock->arena, root->right);
	else if (root->right->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(stock, \
				root->right, 1);
	else if (root->right->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(stock, \
				root->right, 0);
	else if (root->right->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(stock->arena, root->right, 0);
}

t_program	**extract_programs_pipeline(t_stock *stock, \
		t_ast_node *root, t_program **programs, int *i)
{
	if (programs == NULL)
		programs = arena_alloc(stock->arena, \
				sizeof(t_program *) * (2 * PROGRAMS_COUNT + 1));
	extract_programs_pipeline_helper_r(stock, root, i, programs);
	if (root->left->type == NODE_PIPELINE)
		return (extract_programs_pipeline(stock, \
				root->left, programs, i));
	else if (root->left->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(stock->arena, root->left);
	else if (root->left->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(stock->arena, root->left);
	else if (root->left->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(stock, \
				root->left, 1);
	else if (root->left->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(stock, \
				root->left, 0);
	else if (root->left->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(stock->arena, root->left, 0);
	programs[*i] = NULL;
	return (programs);
}
