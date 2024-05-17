/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isTreeValid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:17:05 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/17 14:12:04 by yzioual          ###   ########.fr       */
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
	if (ft_strcmp(s, ">") == 0 ||
		ft_strcmp(s, "<") == 0 ||
		ft_strcmp(s, "<<") == 0 ||
		ft_strcmp(s, ">>") == 0)
	{
		return (true);
	}
	return (false);
}

bool	check_first_last_token(t_list *tokens, int size)
{
	t_node	*temp;

	if (tokens == NULL)
		return (false);
	temp = tokens->head;
	if ((ft_strcmp(temp->data, "|") == 0) || (is_op(temp->data) && size == 1))
		return (false);
	while (temp->next != NULL)
		temp = temp->next;
	if (ft_strcmp(temp->data, "|") == 0 || is_op(temp->data)) 
		return (false);
	return (true);
}

bool	is_input_valid(t_list *tokens)
{
	t_node	*temp;
	char	*token;
	int	size;	

	size = tokens_size(tokens);
	temp = tokens->head;
	if (!check_first_last_token(tokens, size))
	{
		printf("Input is not valid\n");
		return (false);
	}
	while (temp != NULL)
	{
		token = temp->data;
		if (size == 1 && (strcmp(token, "|") == 0 \
					|| strcmp(token, ">") == 0 || \
					strcmp(token, "<") == 0 || strcmp(token, ">>") \
					== 0 || strcmp(token, "<<") == 0))
		{
			printf("Input is not valid\n");
			return (false);
		}
		else if ((is_op(temp->data) && is_op(temp->next->data)) || (ft_strcmp(temp->data, "|") == 0 && temp->next &&ft_strcmp(temp->next->data, "|") == 0))
		{
			printf("Input is not valid\n");
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}
