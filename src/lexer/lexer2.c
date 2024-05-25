/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:17 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 17:00:50 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_special_chars(t_arena *arena, const char **s, t_list **list)
{
	if (**s == '>')
	{
		if (*(*s + 1) == '>')
		{
			append(arena, *list, ft_strdup(arena, ">>"), TOKEN_REDIR_APPEND);
			(*s)++;
		}
		else
			append(arena, *list, ft_strdup(arena, ">"), TOKEN_REDIR_OUT);
	}
	else if (**s == '<')
	{
		if (*(*s + 1) == '<')
		{
			append(arena, *list, ft_strdup(arena, "<<"), TOKEN_REDIR_HEREDOC);
			(*s)++;
		}
		else
			append(arena, *list, ft_strdup(arena, "<"), TOKEN_REDIR_IN);
	}
	else if (**s == '|')
		append(arena, *list, ft_strdup(arena, "|"), TOKEN_PIPE);
	(*s)++;
}

void	ign_redir(t_list **list)
{
	t_node	*temp;
	t_node	*next;

	temp = (*list)->head;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->data && ft_strstr(temp->data, "echo"))
		{
			if (next && next->data && (ft_strcmp(next->data, \
				"<") == 0 || ft_strcmp(next->data, "<<") == 0))
			{
				next = next->next;
				if (next)
					next = next->next;
				temp->next = next;
			}
		}
		temp = temp->next;
	}
}
