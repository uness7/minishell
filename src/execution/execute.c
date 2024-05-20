/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:07:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 16:36:12 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redir_out_append(int type)
{
	return (type == NODE_REDIRECTION_OUT || type == NODE_REDIRECTION_APPEND);
}

t_program	**extract_programs(t_arena *arena, \
		t_ast_node *root, int programs_count)
{
	t_program	**programs;
	int			i;

	i = 0;
	programs = arena_alloc(arena, sizeof(t_program *) \
			* (2 * programs_count + 1));
	if (root->type == NODE_COMMAND)
		programs[i++] = extract_program_command(arena, root);
	else if (root->type == NODE_REDIRECTION_IN)
		programs[i++] = extract_program_redir_in(arena, root);
	else if (is_redir_out_append(root->type))
	{
		if (root->type == NODE_REDIRECTION_OUT)
			programs[i++] = extract_program_redir_out_append(arena, root, 1);
		else
			programs[i++] = extract_program_redir_out_append(arena, root, 0);
	}
	else if (root->type == NODE_REDIRECTION_HEREDOC)
		programs[i++] = extract_program_heredoc(arena, root, 0);
	else if (root->type == NODE_PIPELINE)
		return (extract_programs_pipeline(arena, root, programs, &i));
	programs[i] = NULL;
	return (programs);
}
