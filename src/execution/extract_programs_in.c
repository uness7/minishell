/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_programs_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:48:12 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/19 11:44:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_out(t_arena *arena, t_ast_node *root)
{
	int		fd;
	int		fd_out;
	char	*file;

	fd = -1;
	fd_out = fd;
	if (root->left)
	{
		while (root->left)
		{
			file = ft_strdup(arena, root->left->data);
			if (root->left->f_out == 1)
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (root->left->f_out == 2)
				fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (-1);
			root->left = root->left->left;
		}
		fd_out = fd;
	}
	return (fd_out);
}

static int	get_fd_in(t_arena *arena, t_ast_node *root)
{
	int		fd;
	int		fd_in;
	char	*filename;

	fd = -1;
	fd_in = fd;
	if (root->left != NULL && root->left->data != NULL)
	{
		fd = -1;
		while (root->left != NULL)
		{
			if (root->left->f_out == 1 || root->left->f_out == 2)
				break ;
			filename = ft_strdup(arena, root->left->data);
			fd = open(filename, O_RDONLY);
			if (fd == -1)
				return (-1);
			root->left = root->left->left;
		}
		fd_in = fd;
	}
	return (fd_in);
}

static char	*get_cmd(t_arena *arena, t_ast_node *root)
{
	char	*cmd;

	cmd = NULL;
	if (root->right)
		cmd = ft_strdup(arena, root->right->data);
	return (cmd);
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

t_program	*extract_program_redir_in(t_arena *arena, t_ast_node *root)
{
	t_program	*program;

	program = arena_alloc(arena, sizeof(t_program));
	program->fd_in = 0;
	program->fd_in = get_fd_in(arena, root);
	program->fd_out = 1;
	program->fd_out = get_fd_out(arena, root);
	if (program->fd_in == -1 || program->fd_out == -1)
	{
		perror("Failed to open ");
		return (NULL);
	}
	program->cmd = get_cmd(arena, root);
	program->args = get_args(arena, root);
	program->fd_heredoc = 0;
	program->type = NODE_REDIRECTION_IN;
	return (program);
}
