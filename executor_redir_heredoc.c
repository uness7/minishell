/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:21:32 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/28 15:24:21 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redir_heredoc(char *cmd, char **av, char **envp)
{
	pid_t	id;
	int		status;

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
