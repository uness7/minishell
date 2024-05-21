/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_programs_out_append.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:48:52 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 12:55:44 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_out(t_arena *arena, t_ast_node *root, int f_out)
{
	char	*filename;
	int		fd_out;
	int		fd;

	fd = -1;
	fd_out = 0;
	if (root->left != NULL && root->left->data != NULL)
	{
		while (root->left != NULL)
		{
			filename = ft_strdup(arena, root->left->data);
			filename = trim_single_quotes(arena, filename);
			filename = trim_quotes(arena, filename);
			if (f_out == 1)
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("Failed to open file");
				return (-1);
			}
			root->left = root->left->left;
		}
		fd_out = fd;
	}
	return (fd_out);
}

static char	**get_args(t_arena *arena, t_ast_node *root)
{
	int			j;
	char		**args;
	t_ast_node	*temp;

	j = 0;
	args = arena_alloc(arena, sizeof(char *) * 100);
	temp = root->right;
	while (temp != NULL)
	{
		args[j] = ft_strdup(arena, temp->data);
		j++;
		temp = temp->right;
	}
	args[j] = NULL;
	return (args);
}

static char	*get_cmd(t_arena *arena, t_ast_node *root)
{
	if (root->right == NULL)
		return (NULL);
	return (ft_strdup(arena, root->right->data));
}

t_program	*extract_program_redir_out_append(t_stock *stock, \
		t_ast_node *root, int f_out)
{
	t_program	*program;

	program = arena_alloc(stock->arena, sizeof(t_program));
	program->fd_in = 0;
	program->fd_out = get_fd_out(stock->arena, root, f_out);
	if (program->fd_out == -1)
		return (NULL);
	program->cmd = get_cmd(stock->arena, root);
	if (program->cmd == NULL)
		return (NULL);
	program->args = get_args(stock->arena, root);
	program->fd_heredoc = 0;
	program->type = NODE_REDIRECTION_OUT;
	return (program);
}
