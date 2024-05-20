/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:44:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/20 13:03:08 by yzioual          ###   ########.fr       */
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

void	append_input(char *dest, const char *src, size_t size)
{
	strncat(dest, src, size - strlen(dest) - 1);
}
