/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:07:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/05/14 16:41:42 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// maybe i should implement extract_builtin command

int	run_programs(t_program **programs, char **envp, t_stock *stock, char *input)
{
	pid_t	pid;
	int		i;
	int		pipefd[2];
	int		last_fd;
	char	*path;
		int		next_exists;

	i = 0;
	last_fd = STDIN_FILENO;
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_sig);
	while (programs[i])
	{
		next_exists = programs[i + 1] != NULL;
		if (next_exists && pipe(pipefd) == -1)
		{
			perror("Pipe syscall failed: ");
			exit(EXIT_FAILURE);
		}
		if (_isbuiltin(stock->arena, programs[i]->cmd)) 
			_runbuiltins(stock, input);
		else
		{
			path = find_cmd(stock->arena, ft_strtok(stock->arena, \
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
				if (strncmp(programs[i]->cmd, "./", 2) == 0 || strncmp(programs[i]->cmd, "/", 1) == 0)
					execve(programs[i]->cmd, programs[i]->args, envp);
				else
					execve(path, programs[i]->args, envp);
				printf("Command Not Found\n");
				exit(127);
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
		}
		i++;
	}
	if (last_fd != STDIN_FILENO)
		close(last_fd);
	int	status = 0;
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
	program->fd_heredoc = 0;
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
	if (root->left != NULL && root->left->data != NULL)
	{
		fd = -1;
		while (root->left != NULL)
		{
			filename = strdup(root->left->data);
			//printf("%s\n", filename);
			if (filename == NULL) return (NULL);
			fd = open(filename, O_RDONLY);
			if (fd == -1)
			{
				perror("Failed to open file");
				return (NULL);
			}
			if (root->left->f_out != 0)
				break ;
			root->left = root->left->left;
		}
		program->fd_in = fd;
	}
	program->fd_out = 1;
	if (root->left && root->left->f_out == 1)
	{
		char	*file;
		int	fd;

		file = strdup(root->left->data);
		if (file == NULL) return NULL;
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Failed to open file");
			return (NULL);
		}
		program->fd_out = fd;
	}
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
	program->fd_heredoc = 0;
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
	if (root->left != NULL && root->left->data != NULL)
	{
		while (root->left != NULL)
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
			root->left = root->left->left;
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
	program->fd_heredoc = 0;
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

	if (root->right->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(root->right);
	else if (root->right->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(root->right);
	else if (root->right->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(root->right, 1);
	else if (root->right->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(root->right, 0);
	else if (root->right->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(root->right);

	if (root->left->type == NODE_PIPELINE)
		return extract_programs_pipeline(root->left, programs,\
				programs_count, i);
	else if (root->left->type == NODE_COMMAND)
		programs[(*i)++] = extract_program_command(root->left);
	else if (root->left->type == NODE_REDIRECTION_IN)
		programs[(*i)++] = extract_program_redir_in(root->left);
	else if (root->left->type == NODE_REDIRECTION_OUT)
		programs[(*i)++] = extract_program_redir_out_append(root->left, 1);
	else if (root->left->type == NODE_REDIRECTION_APPEND)
		programs[(*i)++] = extract_program_redir_out_append(root->left, 0);
	else if (root->left->type == NODE_REDIRECTION_HEREDOC)
		programs[(*i)++] = extract_program_heredoc(root->left);

	programs[*i] = NULL;
	return (programs);
}

int	heredoc(char *start_delim, char *end_delim, const char *filename)
{
	int		nbytes, len_start, len_end;
	char	buff[BUFFERSIZE + 1];
	int		fd;

	if (start_delim != NULL)
		len_start = strlen(start_delim);
	len_end = strlen(end_delim);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return -1;
	if (start_delim != NULL)
	{
		write(1, "heredoc> ", 9);
		while ((nbytes = read(0, buff, BUFFERSIZE)) > 0)
		{
			if (nbytes == -1 && errno == EINTR)
				break ;
			buff[nbytes] = 0;
			if (nbytes == len_start + 1 && (memcmp(start_delim, buff, len_start) == 0) && buff[nbytes - 1] == '\n') {
				break;
			}
			write(1, "heredoc> ", 9);
		}
	}
	write(1, "heredoc> ", 9);
	while ((nbytes = read(0, buff, BUFFERSIZE)) > 0)
	{
			if (nbytes == -1 && errno == EINTR)
				break ;
		buff[nbytes] = 0;
		if (nbytes == len_end + 1 && (memcmp(end_delim, buff, len_end) == 0) && buff[nbytes - 1] == '\n') {
			break;
		}
		write(fd, buff, nbytes);
		write(1, "heredoc> ", 9);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	return fd;
}

void write_file_to_stdout(int fd) {
    ssize_t nbytes;
    char buffer[BUFFERSIZE];

    while ((nbytes = read(fd, buffer, BUFFERSIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, nbytes) != nbytes) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (nbytes == -1) {
        perror("read");
    }

    // Close the file descriptor
    close(fd);
}


t_program	*extract_program_heredoc(t_ast_node *root)
{
	int		j;
	char	*deli;
	char	*deli2;
	t_ast_node	*temp;
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (program == NULL) return NULL;
	program->fd_out = 1;	
	deli = NULL;
	deli2 = NULL;

	t_ast_node	*curr = root->right;
	t_ast_node	*prev = NULL;

	while (curr->right != NULL)
	{
		prev = curr;
		curr = curr->right;
	}

	if (prev != NULL) 
		deli = strdup(prev->data);
	 if (curr != NULL)
		deli2 = curr->data;

	 /*
	 printf("deli 1: %s\n", deli);
	 printf("deli 2 : %s\n", deli2);
	 exit(0);
	 */

	program->fd_in = heredoc(deli, deli2, "tmp.txt");
	unlink("tmp.txt");
//	printf("%d\n", program->fd_in);

//	write_file_to_stdout(program->fd_in);	

//	exit(0);

	//program->fd_in = 1;
	if (root->left->type == NODE_COMMAND)
		program->cmd = strdup(root->left->data);	

	if (program->cmd == NULL) return NULL;

	program->args = malloc(sizeof(char *) * 100);
	if (program->args == NULL) return NULL;
	j = 0;
	program->args[j++] = strdup(program->cmd);
	temp = root->left->right;
	while (temp != NULL)
	{
		//printf("arg : %s\n", root->left->right->data);
		program->args[j] = strdup(temp->data);
		if (program->args[j]  == NULL) return NULL;
		j++;
		temp = temp->right;
	}
	program->type = NODE_REDIRECTION_HEREDOC;
	program->args[j] = NULL;
	return (program);
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
	else if (root->type == NODE_REDIRECTION_HEREDOC)
		programs[i++] = extract_program_heredoc(root);
	else if (root->type == NODE_PIPELINE)
	{
		programs = extract_programs_pipeline(root, programs, programs_count, &i);
		return (programs);
	}
	programs[i] = NULL;
	return (programs);
}
