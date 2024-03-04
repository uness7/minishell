/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:31:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/04 10:49:45 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**lexer(const char **input)
{
	t_token	**tokens;


	tokens = malloc(sizeof(t_token) * ));
}

/*
 *
 	Test 1:

	int	main(int ac, char **av)
	{
		char	*input = "ls ­al | grep me > file1";
		t_token	**tokens = lexer(&input);
	}

 * */
