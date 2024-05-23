/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:16 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/23 15:39:17 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ends_with_pipe(char *s)
{
	char	*cpy;

	cpy = s;
	while (*cpy && *(cpy + 1))
		cpy++;
	if (*cpy == '|')
		return (true);
	return (false);
}

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
