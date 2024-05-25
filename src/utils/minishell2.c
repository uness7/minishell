/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:35:07 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 14:00:31 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes_or_pipe(t_arena *arena, char *input)
{
	(void)arena;
	if (has_unclosed_quotes(input))
		return (-1);
	return (0);
}

void	ign_cmd(t_program ***programs)
{
	int	i;
	int	j;

	i = 0;
	while ((*programs)[i] != NULL)
	{
		if ((*programs)[i]->cmd == NULL)
		{
			j = i;
			while ((*programs)[j] != NULL)
			{
				(*programs)[j] = (*programs)[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

size_t	list_size(t_list *list)
{
	size_t	size;
	t_node	*current;

	size = 0;
	current = list->head;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	update_status(t_stock *stock)
{
	if (g_status != 0)
		*(stock->status) = g_status;
}

void	err_message(t_stock *stock, int code)
{
	if (code == 127)
	{
		dprintf(2, "  command not found");
		*(stock->status) = 127;
	}
	else if (code == 1)
		*(stock->status) = 1;
}
