/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isListValid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:17:05 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 13:20:06 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_cnd(t_node *temp)
{
	return ((is_op(temp->data) && is_op(temp->next->data))
		|| (ft_strcmp(temp->data, "|") == 0 && temp->next
			&& ft_strcmp(temp->next->data, "|") == 0));
}

static bool	check_cnd2(char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

static bool	input_invalid(void)
{
	printf("Input is not valid\n");
	return (false);
}

bool	is_input_valid(t_list *tokens)
{
	t_node	*temp;
	char	*token;
	int		size;

	size = tokens_size(tokens);
	temp = tokens->head;
	if (!check_first_last_token(tokens, size))
		input_invalid();
	while (temp != NULL)
	{
		token = temp->data;
		if (size == 1 && (check_cnd2(token)))
			input_invalid();
		else if (check_cnd(temp))
			input_invalid();
		temp = temp->next;
	}
	return (true);
}
