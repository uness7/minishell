/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isListValid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:17:05 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/21 12:48:05 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_cnd(t_node *temp)
{
	if (!temp || !temp->next)
		return (false);
	return ((is_op(temp->data) && is_op(temp->next->data))
		|| (ft_strcmp(temp->data, "|") == 0 && temp->next
			&& ft_strcmp(temp->next->data, "|") == 0));
}

static bool	check_cnd2(char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

bool	is_input_valid(t_list *tokens)
{
	t_node	*temp;
	char	*token;
	int		size;

	size = tokens_size(tokens);
	temp = tokens->head;
	if (!check_first_last_token(tokens, size))
		return (false);
	while (temp != NULL)
	{
		token = temp->data;
		if ((size == 1 && check_cnd2(token)) || check_cnd(temp))
			return (false);
		temp = temp->next;
	}
	return (true);
}
