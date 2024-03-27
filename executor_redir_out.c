#include "minishell.h"

void	*malloc_err(void)
{
	printf("Error allocating memory\n");
        return (NULL);
}

t_redir_cmd	*build_cmd_redir_out(t_ast_node *root)
{
	t_redir_cmd	*result;

	result = malloc(sizeof(t_redir_cmd));
	if (result == NULL)
		malloc_err();
	if (root->left->type == NODE_ARGUMENT)
	{
		result->av = build_command(root->right);
		result->target = strdup(root->left->data);
		if (result->target == NULL)
			malloc_err();
	}
	else
	{
		result->av = build_command(root);
		result->target = strdup(root->right->data);
		if (result->target == NULL)
			malloc_err();
	}
	return (result);
}

void	execute_redir_out(char *cmd_path, char *target, char **av, char **envp)
{
	pid_t	id;
	int		status;
	int		fd;

	if (target == NULL)
	{
		printf("target is null\n");exit(1);
	}
	fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open ");
		exit(EXIT_FAILURE);
	}
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
	close(fd);
	return ;
}
