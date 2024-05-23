/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_programs_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:50:12 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/23 18:36:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_delims	*get_delims(t_arena *arena, t_ast_node *root)
{
	t_delims	*delims;
	t_ast_node	*curr;
	t_ast_node	*prev;

	curr = root->right;
	prev = NULL;
	delims = arena_alloc(arena, sizeof(t_delims) * 3);
	while (curr->right != NULL)
	{
		prev = curr;
		curr = curr->right;
	}
	if (prev != NULL)
		delims->deli = ft_strdup(arena, prev->data);
	if (curr != NULL)
		delims->deli2 = ft_strdup(arena, curr->data);
	return (delims);
}

static char	*get_cmd(t_arena *arena, t_ast_node *root)
{
	if (root->left == NULL || root->left->data == NULL)
		return (NULL);
	return (ft_strdup(arena, root->left->data));
}

static char	**get_args(t_arena *arena, t_ast_node *root, char *cmd)
{
	t_ast_node	*temp;
	int			j;
	char		**args;

	args = arena_alloc(arena, sizeof(char *) * 100);
	j = 0;
	args[j++] = ft_strdup(arena, cmd);
	temp = root->left->right;
	while (temp != NULL)
	{
		args[j] = ft_strdup(arena, temp->data);
		j++;
		temp = temp->right;
	}
	args[j] = NULL;
	return (args);
}

static int	get_fd_out(t_arena *arena, t_ast_node *root)
{
	int			fd;
	int			fd_out;
	char		*file;
	t_ast_node	*temp;

	fd = 1;
	temp = root->left;
	while (temp->left != NULL)
	{
		file = ft_strdup(arena, temp->left->data);
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		temp = temp->left;
	}
	fd_out = fd;
	return (fd_out);
}

t_program	*extract_program_heredoc(t_arena *arena, t_ast_node *root,
		int f_no_cmd)
{
	t_program	*program;
	t_delims	*delims;

	f_no_cmd = 0;
	if (root->left == NULL)
		f_no_cmd = 1;
	program = arena_alloc(arena, sizeof(t_program));
	delims = get_delims(arena, root);
	program->fd_in = heredoc(trim_single_quotes(arena, trim_quotes(arena,
					delims->deli)), trim_single_quotes(arena, trim_quotes(arena,
					delims->deli2)), "tmp.txt");
	if (program->fd_in == -1)
		return (NULL);
	unlink("tmp.txt");
	if (f_no_cmd == 1)
		return (NULL);
	program->fd_out = 1;
	program->fd_out = get_fd_out(arena, root);
	program->cmd = get_cmd(arena, root);
	program->args = get_args(arena, root, program->cmd);
	program->type = NODE_REDIRECTION_HEREDOC;
	return (program);
}
