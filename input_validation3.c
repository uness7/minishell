/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:59:56 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/27 12:55:31 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input_valid2(char *s)
{
	if (ft_strcmp(s, ">") == 0)
		return (false);
	else if (ft_strcmp(s, "<") == 0)
		return (false);
	else if (ft_strcmp(s, "|") == 0)
		return (false);
	else if (ft_strcmp(s, ">>") == 0)
		return (false);
	else if (ft_strcmp(s, "<<") == 0)
		return (false);
	return (true);
}

bool	is_input_valid(char *s)
{
	return (!(has_double_unclosed_quotes(s) || has_single_unclosed_quotes(s)));
}
