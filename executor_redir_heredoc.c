/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:21:32 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/28 17:23:46 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_heredoc	*build_cmd_redir_heredoc(t_ast_node *root)
{
	t_redir_heredoc	*result;

	result = malloc(sizeof(t_redir_heredoc));
	if (result == NULL)
		malloc_err();
	if (root->left->type == NODE_ARGUMENT)
	{
		result->av = build_command(root->right);
		result->delimeter = strdup(root->left->data);
		if (result->delimeter == NULL)
			malloc_err();
	}
	else
	{
		result->av = build_command(root->left);
		result->delimeter = strdup(root->right->data);
		if (result->delimeter == NULL)
			malloc_err();
	}
	return (result);
}

// we need to free memory
char	**get_input(char *eof)
{
	char	*input;
	char	**result;
	int count = 0;

	result = malloc(sizeof(char *) * 100);
	if (result == NULL)
		malloc_err();

	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL)
		{
			free(result);
			return (NULL);
		}
		if (strcmp(input, eof) == 0)
		{
			free(input);
			break ;
		}
		result[count] = strdup(input);
		if (result[count] == NULL)
		{
			free(input);
			while (count > 0)
			{
				free(result[count - 1]);
				count--;
			}
			free(result);
			return (NULL);
		}
		count++;

		free(input);
	}
	result[count] = NULL;
	return (result);
}

void	execute_redir_heredoc(char *cmd, char **input, char **av, char **envp)
{
	pid_t	id;
	int		status;

	//
	while (*av != NULL)
		av++;
	
	av = input;
	//
	id = fork();
	status = 0;
	if (id == 0)
	{
		if (execve(cmd, av, envp) == -1)
			perror("execve : ");
		exit(EXIT_FAILURE);
	}
	else if (id < 0)
	{
		perror("fork :");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(id, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(id, &status, WUNTRACED);
	}
	return ;
}
