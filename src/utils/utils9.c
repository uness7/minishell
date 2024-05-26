/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:10:51 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/26 17:08:13 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_sign_and_whitespace(char **str)
{
	int	sign;

	sign = 1;
	while (ft_isspace((unsigned char)**str))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

void	check_endptr(char **endptr, char *str)
{
	if (endptr)
		*endptr = str;
}

long long	convert_to_long(char *str, char **endptr, int base, int sign)
{
	long long	result;
	int			digit;

	result = 0;
	if (base != 10)
	{
		check_endptr(endptr, str);
		return (0);
	}
	while (ft_isdigit((unsigned char)*str))
	{
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			errno = ERANGE;
			check_endptr(endptr, str);
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	check_endptr(endptr, str);
	return (result * sign);
}

long long	ft_strtoll(char *str, char **endptr, int base)
{
	int	sign;

	sign = handle_sign_and_whitespace(&str);
	return (convert_to_long(str, endptr, base, sign));
}
