/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/26 18:01:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
    	(void)argv;
	char		*input;
	char		**av;
	char	*paths;
	char	*cmd;
	char	**cmd_path;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;

		paths = find_paths(envp);
		cmd_path = ft_strtok(paths);
		av = build_command(parse(tokenize(input)));
		cmd = find_cmd(cmd_path, av[0]);

		execute(cmd, av, envp);

		free(av);
		free(input);
	}
	return (0);
}
