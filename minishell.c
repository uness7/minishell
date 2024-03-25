/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/25 18:11:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(void)
{
	char	*input;
	t_ast_node	*tree;

	while (1)
	{
		input =	readline("minishell> ");
        	tree = parse(tokenize(input));
		if (tree->type == NODE_COMMAND)
		{
			int i = 0;
			char **av = build_command(tree);
			while (av[i])
			{
				printf("%s\n", av[i]);
				i++;
			}
		}
		free(input);
	}
	return 0;
}
