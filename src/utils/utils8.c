/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:16 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/25 12:29:37 by yzioual          ###   ########.fr       */
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

bool	has_unclosed_quotes(char *str)
{
	int		i;
	bool	inside_single_quote;
	bool	inside_double_quote;

	i = 0;
	inside_single_quote = false;
	inside_double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		else if (str[i] == '"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
		i++;
	}
	return (inside_single_quote || inside_double_quote);
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	dest = str;
	while (i < n)
	{
		dest[i] = (char)c;
		i++;
	}
	return (str);
}
