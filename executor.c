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

# define WORD_SIZE 50

/* Pre-order Tree Traversal */

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

char	**build_command(t_ast_node *root)
{
	char	**av;
	int		number_args;
	int		i;

	i = 0;
	number_args = find_number_nodes(root);
	av = malloc(sizeof(char *) * number_args);
	if (av == NULL)
	{
		printf("Error allocating memory \n");
		return (NULL);
	}
	if (root == NULL)
		return (NULL);
	av[i] = strdup(root->data);
	if (av[i] == NULL)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	i++;	
	build_command(root->left);
	build_command(root->right);
	return (av);
}

void	execute(char **av)
{
	pid_t	id, wid;
	int	status;

	id = fork();
	status = 0;
	if (id == 0)
	{
		if (execvp(av[0], av) == -1)
			perror("exevp : ");
		exit(EXIT_SUCCESS);
	}
	else if (id < 0)
	{
		perror("fork :");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wid = waitpid(id, &status, WUNTRACED);
	}
	return ;
}
