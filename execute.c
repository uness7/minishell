/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:07:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/11 19:36:40 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_programs(t_program **programs, char **envp, t_arena *arena)
{
	pid_t	pid;
	int		i;
	int		pipefd[2];
	int		last_fd;
	char	*path;


	i = 0;
	last_fd = STDIN_FILENO;
	while (programs[i])
	{
		if (programs[i + 1] && pipe(pipefd) == -1)
		{
			perror("Pipe syscall failed: ");
			exit(EXIT_FAILURE);
		}
		path = find_cmd(arena, ft_strtok(arena, \
					find_paths(envp)), programs[i]->cmd);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(last_fd, STDIN_FILENO);
			if (programs[i + 1])
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
			}

			// specific cases
			if (programs[i]->type == NODE_REDIRECTION_IN)
			{
				dup2(programs[i]->fd_in, STDIN_FILENO);
				close(programs[i]->fd_in);
			}
			else if (programs[i]->type == NODE_REDIRECTION_OUT ||
				programs[i]->type == NODE_REDIRECTION_APPEND)
			{
				dup2(programs[i]->fd_out, STDOUT_FILENO);
				close(programs[i]->fd_out);
			}
			else if (programs[i]->type == NODE_REDIRECTION_HEREDOC)
			{
				dup2(programs[i]->fd_in, STDIN_FILENO);
				close(programs[i]->fd_in);
			}
			execve(path, programs[i]->args, envp);
			perror("execve failed: ");
			exit(0);
		}
		else if (pid < 0)
			fork_err();
		if (i > 0)
			close(last_fd);
		if (programs[i + 1])
		{
			close(pipefd[1]);
			last_fd = pipefd[0];
		}
		i++;
	}
	if (last_fd != STDIN_FILENO)
		close(last_fd);
	int	status = 0;
	waitpid(pid, &status, 0);
	//return ;
}

t_program	*extract_program_command(t_ast_node *root)
{
	int		j;
	t_ast_node	*temp;
	t_program	*program;

	j = 0;
	program = malloc(sizeof(t_program));
	if (program == NULL)
		return (NULL);
	program->fd_out = 1;
	program->fd_in = 0;
	program->cmd = strdup(root->data);
	if (program->cmd == NULL) return NULL;
	program->args = malloc(sizeof(char *) * 100);
	if (program->args == NULL)
		return (NULL);
	program->args[j++] = strdup(program->cmd);
	if (root->left != NULL)
	{
		program->args[j] = strdup(root->left->data);
		if (program->args[j] == NULL)
			return NULL;
		j++;
	}
	temp = root->right;
	while (temp != NULL)
	{
		program->args[j] = strdup(temp->data);
		if (program->args[j] == NULL) return NULL;
		j++;
		temp = temp->right;
	}
	program->f_heredoc = 0;
	program->args[j] = NULL;
	program->type = NODE_COMMAND;
	return (program);
}


t_program	*extract_program_redir_in(t_ast_node *root)
{
	int		j;
	int		fd;
	char	*filename;
	t_ast_node	*temp;
	t_program	*program;

	j = 0;
	program = malloc(sizeof(t_program));
	if (program == NULL) return NULL;
	if (root->left != NULL || root->left->data != NULL)
	{
		filename = strdup(root->left->data);
		if (filename == NULL) return (NULL);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror("Failed to open file");
			return (NULL);
		}
		program->fd_in = fd;
	}
	program->fd_out = 1;
	program->cmd = strdup(root->right->data);
	if (program->cmd == NULL)
		return (NULL);
	program->args = malloc(sizeof(char *) * 100);
	temp = root->right;
	while (temp != NULL)
	{
		program->args[j] = strdup(temp->data);
		if (program->args[j] == NULL) return NULL;
		j++;
		temp = temp->right;
	}
	program->f_heredoc = 0;
	program->args[j] = NULL;
	program->type = NODE_REDIRECTION_IN;
	return (program);
}

t_program	*extract_program_redir_out_append(t_ast_node *root, int f_out)
{
	int		j;
	int		fd;
	char	*filename;
	t_ast_node	*temp;
	t_program	*program;

	j = 0;
	program = malloc(sizeof(t_program));
	if (program == NULL) return NULL;
	if (root->left != NULL || root->left->data != NULL)
	{
		filename = strdup(root->left->data);
		if (filename == NULL) return (NULL);
		if (f_out == 1)
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Failed to open file");
			return (NULL);
		}
		program->fd_out = fd;
	}
	program->fd_in = 0;
	program->cmd = strdup(root->right->data);
	if (program->cmd == NULL)
		return (NULL);
	program->args = malloc(sizeof(char *) * 100);
	temp = root->right;
	while (temp != NULL)
	{
		program->args[j] = strdup(temp->data);
		if (program->args[j] == NULL) return NULL;
		j++;
		temp = temp->right;
	}
	program->f_heredoc = 0;
	program->type = NODE_REDIRECTION_OUT;
	program->args[j] = NULL;
	return (program);
}

t_program	**extract_programs_pipeline(t_ast_node *root, t_program **programs , \
		int programs_count, int *i)
{
	if (programs == NULL)
		programs = malloc(sizeof(t_program *) * (2 * programs_count + 1));
	if (programs == NULL) return NULL;
	if (root->left->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(root->left);
	else if (root->left->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(root->left);
	else if (root->left->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(root->left, 1);
	else if (root->left->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(root->left, 0);
	else if (root->left->type == NODE_REDIRECTION_HEREDOC)
	{
		printf("coming soon\n");
		exit(0);
	}
	if (root->right->type == NODE_PIPELINE)
		return extract_programs_pipeline(root->right, programs,\
			       	programs_count, i);
	else if (root->right->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(root->right);
	else if (root->right->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(root->right);
	else if (root->right->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(root->right, 1);
	else if (root->right->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(root->right, 0);
	else if (root->right->type == NODE_REDIRECTION_HEREDOC)
	{
		printf("coming soon\n");
		exit(0);
	}
	programs[*i] = NULL;
	return (programs);
}

t_program	**extract_programs(t_ast_node *root, int programs_count)
{
	int		i;
	t_program	**programs;

	i = 0;
	programs = malloc(sizeof(t_program *) * (2 * programs_count + 1));
	if (programs == NULL)
		return (NULL);
	if (root->type == NODE_COMMAND)
		programs[i++] = extract_program_command(root);
	else if (root->type == NODE_REDIRECTION_IN)
		programs[i++] = extract_program_redir_in(root);
	else if (root->type == NODE_REDIRECTION_OUT ||
		       	root->type == NODE_REDIRECTION_APPEND)
	{
		if (root->type == NODE_REDIRECTION_OUT)
			programs[i++] = extract_program_redir_out_append(root, 1);
		else
			programs[i++] = extract_program_redir_out_append(root, 0);
	}
	else if (root->type == NODE_PIPELINE)
	{
		programs = extract_programs_pipeline(root, programs, programs_count, &i);
		return (programs);
	}
	programs[i] = NULL;
	return (programs);
}
