/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:51:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/25 18:09:24 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WORD_SIZE 50

int	find_number_nodes(t_ast_node *root)
{
	int	number_nodes;

	number_nodes = 1;
	if (root == NULL)
		return (0);
	number_nodes = find_number_nodes(root->left);
	number_nodes = find_number_nodes(root->right);
	return (number_nodes);
}

void	free_str_array(char **s)
{
	while(*s)
		free(*s);
	free(s);
}

char	**build_command(t_ast_node *root)
{
	char	**av;
	int		number_args;
	int		i;
	char	**left_args;
	char	**right_args;

	if (root == NULL)
		return (NULL);
	i = 0;
	number_args = find_number_nodes(root);
	av = malloc(sizeof(char *) * (number_args + 1));
	if (av == NULL)
	{
		printf("Error allocating memory \n");
		return (NULL);
	}
	av[i] = strdup(root->data);
	if (av[i] == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	i++;
	if (root->left)
	{
		left_args = build_command(root->left);
		while (left_args && left_args[i - 1])
		{
			av[i] = strdup(left_args[i - 1]);
			if (av[i] == NULL)
			{
				printf("Error allocating memory\n");
				return (NULL);
			}
			i++;
		}
	}
	if (root->right)
	{
		right_args = build_command(root->right);
		while (right_args && right_args[i - 1])
		{
			av[i] = strdup(right_args[i - 1]);
			if (av[i] == NULL)
			{
				printf("Error allocating memory\n");
				return (NULL);
			}
			i++;
		}
	}
	av[i] = NULL; // NULL-terminate the argument array
	return (av);
}

void	execute(char **av)
{
	pid_t	id;
	int		status;

	id = fork();
	status = 0;
	if (id == 0)
	{
		if (execvp(av[0], av) == -1)
			perror("exevp : ");
	//	exit(0);
	}
	else if (id < 0)
	{
		perror("fork :");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(id, &status, WUNTRACED);
	}
	return ;
}
