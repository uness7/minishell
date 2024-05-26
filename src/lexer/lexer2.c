/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:58:17 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 19:59:04 by yzioual          ###   ########.fr       */
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
