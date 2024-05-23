/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:10:51 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/23 16:14:19 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    ft_isbase(char c, int base)
{
    if (base <= 10)
        return (c >= '0' && c < '0' + base);
    return ((c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + base - 10) ||
            (c >= 'A' && c < 'A' + base - 10));
}

static int    ft_chartoi(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 10);
    return (0);
}

long    ft_strtol(char *str, char **endptr, int base)
{
	long    result = 0;
	int        sign = 1;

	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	if (base == 0)
		base = (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) ? 16 : 10;
	if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (ft_isbase(*str, base))
	{
		if (result > (LONG_MAX - ft_chartoi(*str)) / base)
		{
			errno = ERANGE;
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * base + ft_chartoi(*str++);
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
