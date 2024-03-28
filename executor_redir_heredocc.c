#include "minishell.h"

void	execute_redir_heredocc(char *cmd_path, char **av, char **envp)
{
	pid_t	id;
	int		status;

	status = 0;
	id = fork();
	if (id == 0)
	{
		dup2(fd, 1);
		if (execve(cmd_path, av, envp) == -1)
			perror("execve ");
		exit(EXIT_FAILURE);
	}
	else if (id < 0)
	{
		perror("fork ");
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
