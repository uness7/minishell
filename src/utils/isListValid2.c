/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isListValid2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:13:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/22 16:40:40 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_size(t_list *tokens)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = tokens->head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

bool	is_op(char *s)
{
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<") == 0 || ft_strcmp(s,
			"<<") == 0 || ft_strcmp(s, ">>") == 0)
	{
		return (true);
	}
	return (false);
}

bool	check_first_last_token(t_list *tokens, int size)
{
	t_node	*temp;

	(void)size;
	if (tokens == NULL)
		return (false);
	temp = tokens->head;
	if (ft_strcmp(temp->data, "|") == 0 || is_op(temp->data))
		return (false);
	while (temp->next != NULL)
		temp = temp->next;
	if (is_op(temp->data))
		return (false);
	return (true);
}
