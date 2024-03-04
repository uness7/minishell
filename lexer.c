/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:31:58 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/04 12:20:16 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(const char **input)
{
	// returns the next token after recognition		
}


void	regex_engine(char	*input)
{
	// patterns matching		
}

t_token	**lexer(const char **input)
{
	t_token	**tokens;
	
	tokens = get_next_token(input);
}

/*

 Test 1:
 int	main(int ac, char **av)
 {
 	char	*input = "ls ­al | grep me > file1";
 	t_token	**tokens = lexer(&input);
 }

 */
