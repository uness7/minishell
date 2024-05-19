/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/17 00:22:53 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection_token(int type)
{
	return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static void	dispenser_helper(t_arena *arena, t_ast_node **tree,
		t_cmd_data *data, int f_flag)
{
	if (data->list->head->type == TOKEN_WORD)
		parse_command(arena, tree, data, f_flag);
	else if (data->list->head->type == TOKEN_PIPE)
		parse_pipeline(arena, tree, data->list->head);
	else if (data->list->head->type == TOKEN_REDIR_OUT)
		parse_redir_out(arena, tree, data->list->head->data);
	else if (data->list->head->type == TOKEN_REDIR_APPEND)
		parse_redir_append(arena, tree, data->list->head->data);
	else if (data->list->head->type == TOKEN_REDIR_IN)
		parse_redir_in(arena, tree, data->list->head->data);
	else if (data->list->head->type == TOKEN_REDIR_HEREDOC)
		parse_redir_heredoc(arena, tree, data->list->head->data);
}

t_ast_node	*parser_dispenser(t_arena *arena, t_list *list)
{
	int			f_flag;
	t_ast_node	*tree;
	t_cmd_data	*data;

	f_flag = 0;
	tree = NULL;
	data = arena_alloc(arena, sizeof(t_cmd_data));
	data->list = list;
	data->prev_token = NULL;
	while (list->head != NULL)
	{
		data->token = list->head;
		if (data->prev_token && is_redirection_token(data->prev_token->type))
			f_flag = 1;
		dispenser_helper(arena, &tree, data, f_flag);
		f_flag = 0;
		data->prev_token = list->head;
		if (list->head != NULL)
			list->head = list->head->next;
	}
	return (tree);
}

t_ast_node	*parse(t_arena *arena, t_list *stream)
{
	return (parser_dispenser(arena, stream));
}
