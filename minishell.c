/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:24:25 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/28 17:03:57 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
    	(void)argv;
	char		*input;
	char	**av;
	char	*cmd;
	t_ast_node	*tree;
	t_redir_cmd	*redir;
	t_redir_heredoc	*redir_heredoc;

	while (1)
	{
		printf("\033[0;31m");
		input = readline("minishell> ");
		if (input == NULL)
			break ;

		tree = parse(tokenize(input));
		if (tree == NULL)
			break ;
 		if (tree->type == NODE_COMMAND)
		{
			av = build_command(tree);
			cmd = find_cmd(ft_strtok(find_paths(envp)), av[0]);
			execute(cmd, av, envp);
			free(av);
		}
		else if (tree->type == NODE_REDIRECTION_OUT)
		{
			redir = build_cmd_redir_out(tree);	
			cmd = find_cmd(ft_strtok(find_paths(envp)), redir->av[0]);
			execute_redir_out(cmd, redir->target, redir->av, envp);
		}
		else if (tree->type == NODE_REDIRECTION_APPEND)
		{
			redir = build_cmd_redir_append(tree);
			cmd = find_cmd(ft_strtok(find_paths(envp)), redir->av[0]);
			execute_redir_append(cmd, redir->target, redir->av, envp);
		}
		else if (tree->type == NODE_REDIRECTION_HEREDOC)
		{
			char **input;

			redir_heredoc = build_cmd_redir_heredoc(tree);
			input = get_input(redir_heredoc->delimeter);
			cmd = find_cmd(ft_strtok(find_paths(envp)), redir_heredoc->av[0]);
			execute_redir_heredoc(cmd, input, av, envp);
		}
		else if (tree->type == NODE_REDIRECTION_IN)
		{
			printf("inppppuuuuuuuuuuuuuuuut\n");
			exit(0);
		}
		else if (tree->type == NODE_PIPELINE)
		{
			printf("oooooooooops\n");
			exit(0);
		}
		free(input);
	}
	return (0);
}
