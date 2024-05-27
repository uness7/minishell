/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_program_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:47:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/27 10:27:44 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	*extract_program_command(t_stock *stock, t_ast_node *root)
{
	int			j;
	t_ast_node	*temp;
	t_program	*program;

	j = 0;
	program = arena_alloc(stock->arena, sizeof(t_program));
	program->fd_out = 1;
	program->fd_in = 0;
	program->cmd = ft_strdup(stock->arena, root->data);
	program->args = arena_alloc(stock->arena, sizeof(char *) * 100);
	program->args[j++] = ft_strdup(stock->arena, program->cmd);
	if (root->left != NULL)
		program->args[j++] = ft_strdup(stock->arena, root->left->data);
	temp = root->right;
	while (temp != NULL)
	{
		program->args[j] = ft_strdup(stock->arena, temp->data);
		j++;
		temp = temp->right;
	}
	program->fd_heredoc = 0;
	program->args[j] = NULL;
	program->type = NODE_COMMAND;
	return (program);
}
