/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:42:27 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/05/04 16:13:45 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_n_option(char ***args, char *str, int *all_n)
{
	int	j;

	j = 0;
	if (str[0] == '-' && ft_strlen(str) > 1)
	{
		*all_n = 1;
		j = 1;
		while ((size_t)j < ft_strlen(str))
		{
			if (str[j] != 'n')
			{
				*all_n = 0;
				break ;
			}
			j++;
		}
		if (*all_n)
			(*args)++;
	}
}

static void	print_value(char **args)
{
	char	*temp;

	while (*args)
	{
		temp = *args;
		if (ft_strstr(temp, "-"))
			handle_n_arg(temp);
		else
		{
			if (ft_strncmp(temp, "\"", 1) == 0 || ft_strncmp(temp, "'", 1) == 0)
				temp++;
			printf("%s", temp);
		}
		printf(" ");
		args++;
	}
}

int	ft_echo(t_arena *arena, char *input, char **envp_cp)
{
	char	**args;
	char	**temp;
	int		n_flag;
	int		all_n;

	(void)envp_cp;
	(void)arena;
	args = ft_split_2(input);	
	args++;
	n_flag = 0;
	if (ft_strncmp(*args, "-", 1) == 0)
	{
		temp = args;
		temp++;
		while (*temp)
		{
			check_n_option(&args, *temp, &all_n);
			temp++;
		}
		check_n_arg(&n_flag, args);
		if (n_flag == 1)
			args++;
	}
	print_value(args);
	if (n_flag == 0)
		printf("\n");
	return (0);
}
