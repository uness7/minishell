/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 16:06:17 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

typedef enum e_token_type
{
	TOKEN = 100,
	TOKEN_PIPE = 101,
	TOKEN_DOUBLE_QUOTES = 102,
	TOKEN_SINGLE_QUOTES = 103,
	TOKEN_SINGLE_REDIR = 104,
	TOKEN_DOUBLE_REDIR = 105
}		t_token_type;

typedef struct s_node
{
	char						*data;
	t_token_type				type;
	struct s_node				*next;
}		t_node;

typedef struct s_list
{
	t_node						*head;
}		t_list;

/* Abstract Syntac Tree */

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPELINE,
	NODE_REDIRECTION
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type	type;
	union 
	{
		char	*command;
		char	*argument;
		struct 
		{
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		}	pipeline;
		struct 
		{
			char	*operator;
			char	*filename;
		}	redirection;
	}	data;
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
t_ast_node	*parse_command(t_token_type type, t_ast_node *root, const char *data);

// trees.c file
t_ast_node      *create_node_tree(bool arg, t_token_type type, const char *data);
void	print_tree(t_ast_node *root, int depth);

#endif
