/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/25 18:06:50 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <wait.h>


typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_ENV_VAR
}		t_token_type;

typedef struct s_node
{
	char		*data;
	t_token_type	type;
	struct s_node	*next;
}		t_node;

typedef struct s_list
{
	t_node	*head;
}	t_list;

/* Abstract Syntac Tree */
typedef enum e_node_type
{
	NODE_COMMAND=1,
	NODE_ARGUMENT=2,
	NODE_PIPELINE,
	NODE_REDIRECTION_OUT,
	NODE_REDIRECTION_IN,
	NODE_REDIRECTION_APPEND,
	NODE_REDIRECTION_HEREDOC,
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type		type;
	char			*data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;


// linkedList.c file
t_node *create_node_list(char *data, t_token_type type);
void init_list(t_list *list);
void append(t_list *list, char *data, t_token_type type);
void print_list(t_list *list);
	
// lexer.c file
t_token_type get_char_type(char c);
t_list *tokenize(const char *s);

// parser.c file
t_ast_node	*parse(t_list *stream);
void	parse_command(t_ast_node **root, const char *data);
void	parse_pipeline(t_ast_node **root, char *data);

// trees.c file
t_ast_node      *create_node_tree(t_node_type type, const char *data);
void	print_tree(t_ast_node *root);


// executor.c file
char	**build_command(t_ast_node *root);
void	execute(char **av);
int		find_number_nodes(t_ast_node *root);
#endif
