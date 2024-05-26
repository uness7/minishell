/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:50:09 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/26 13:24:34 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_helper_2(t_stock *stock, char *word, char *name, char *value)
{
	int	err_flag;

	err_flag = 0;
	name = ft_strtok_2(word, "=");
	if (!name || ft_isdigit(name[0]) || !check_env_var_rules(name))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		err_flag = 1;
	}
	else
	{
		value = ft_strtok_2(NULL, "=");
		if (value == NULL)
			value = ft_strdup(stock->arena, "");
		if (ft_strncmp(value, "\"", 1) != 0 && ft_strncmp(value, "\'", 1) != 0)
			value = ft_strtok_2(value, " ");
		else
			++value;
		if (value != NULL && name != NULL)
			add_or_update_env(stock->env_arena, &(stock->env), name, value);
	}
	return (err_flag);
}
