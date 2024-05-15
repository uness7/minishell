/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:59:56 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/15 11:56:16 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ends_with_pipe(t_arena *arena, char *s)
{
	char	*copy;
	int	i = 0;

	copy = ft_strdup(arena, s);
	while (copy[i])
	{
		if (copy[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

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
	else if (ft_strcmp(s, "|") == 0 || \
			ft_strncmp(s, "|", 1) == 0  \
			|| ft_strncmp(s, "||", 2) == 0)
		return (false);
	else if (ft_strncmp(s, "<|", 2) == 0 || ft_strncmp(s, ">|", 2) == 0)
		return (false);
	return (true);
}

bool	is_input_valid(char *s)
{
	return (!(has_double_unclosed_quotes(s) || has_single_unclosed_quotes(s)));
}
