/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:07:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 15:52:56 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redir_out_append(int type)
{
	return (type == NODE_REDIRECTION_OUT || type == NODE_REDIRECTION_APPEND);
}

t_program	**extract_programs(t_stock *stock, \
		t_ast_node *root, int programs_count)
{
	t_program	**programs;
	int			i;

	i = 0;
	programs = arena_alloc(stock->arena, sizeof(t_program *) \
			* (2 * programs_count + 1));
	if (root->type == NODE_COMMAND)
	{
		programs[i] = extract_program_command(stock->arena, root);
		if (programs[i] == NULL)
			return (NULL);
		i++;
	}
	else if (root->type == NODE_REDIRECTION_IN)
	{
		programs[i] = extract_program_redir_in(stock->arena, root);
		if (programs[i] == NULL)
			return (NULL);
		i++;
	}
	else if (is_redir_out_append(root->type))
	{
		if (root->type == NODE_REDIRECTION_OUT)
			programs[i] = extract_program_redir_out_append(stock, root, 1);
		else
			programs[i] = extract_program_redir_out_append(stock, root, 0);
		if (programs[i] == NULL)
			return NULL;
		i++;
	}
	else if (root->type == NODE_REDIRECTION_HEREDOC)
	{
		programs[i] = extract_program_heredoc(stock->arena, root, 0);
		if (programs[i] == NULL)
			return (NULL);
	}
	else if (root->type == NODE_PIPELINE)
		return (extract_programs_pipeline(stock, root, programs, &i));
	programs[i] = NULL;
	return (programs);
}
