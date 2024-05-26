/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:07:04 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/26 13:26:16 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *list)
{
	t_env	*current;

	if (list == NULL)
	{
		ft_putstr_fd("env list is empty \n", 2);
		exit(0);
	}
	current = list;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, "?") != 0)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
