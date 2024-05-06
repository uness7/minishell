/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:53 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/29 20:05:07 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_single_unclosed_quotes(char *s)
{
	bool	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\'')
			flag = !flag;
		s++;
	}
	return (flag);
}

bool	has_double_unclosed_quotes(char *s)
{
	bool	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\"')
			flag = !flag;
		s++;
	}
	return (flag);
}

bool	has_logical_ops(char *s)
{
	while (*s)
	{
		if ((*s == '&' && *(s + 1) == '&') || (*s == '|' && *(s + 1) == '|'))
			return (true);
		s++;
	}
	return (false);
}

static bool	check6(t_node *temp)
{
	if (temp->type == TOKEN_PIPE)
	{
		if (temp->next->type == TOKEN_REDIR_IN
			|| temp->next->type == TOKEN_REDIR_OUT
			|| temp->next->type == TOKEN_REDIR_APPEND
			|| temp->next->type == TOKEN_REDIR_HEREDOC
			|| temp->next->type == TOKEN_PIPE)
		{
			printf("Syntax error. \n");
			return (false);
		}
	}
	return (true);
}

bool	check_invalid_combinations(t_arena *arena, t_list *list, t_env *env)
{
	t_node	*temp;

	(void)env;
	(void)arena;
	temp = list->head;
	while (temp != NULL && temp->next != NULL)
	{
		if (!check1(temp) || !check2(temp) || !check3(temp) || !check4(temp)
			|| !check5(temp) || !check6(temp))
			return (false);
		temp = temp->next;
	}
	return (true);
}
