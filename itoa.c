/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:57:28 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/24 22:00:26 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_len(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_handle_special_cases(t_arena *arena, char *result, int n)
{
	if (n == -2147483648)
	{
		result = arena_alloc(arena, 12 * sizeof(char));
		if (!result)
			return (NULL);
		ft_strcpy(result, "-2147483648");
		return (result);
	}
	else if (n == 0)
	{
		result = arena_alloc(arena, 2 * sizeof(char));
		if (!result)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	return (NULL);
}

static void	ft_populate_digits(int i, int sign, int n, char *result)
{
	while (i >= 0)
	{
		result[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	if (sign == -1)
		result[0] = '-';
}

char	*ft_itoa(t_arena *arena, int n)
{
	char	*result;
	int		count;
	int		i;
	int		sign;

	sign = 1;
	if (n == 0 || n == -2147483648)
		return (ft_handle_special_cases(arena, NULL, n));
	count = ft_count_len(n);
	if (n < 0 && n != -2147483648)
	{
		sign = -1;
		n = -n;
	}
	result = arena_alloc(arena, count + 1);
	if (!result)
		return (NULL);
	result[count] = '\0';
	i = count - 1;
	ft_populate_digits(i, sign, n, result);
	return (result);
}
