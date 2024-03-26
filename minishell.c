/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/26 16:32:47 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	char		**av;
	t_ast_node	*tree;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		tree = parse(tokenize(input));
		av = build_command(tree);
		execute(av);
		free(av);
		free(input);
	}
	return (0);
}


/***

***/
