#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum e_token_type
{
	TOKEN=100,
	TOKEN_UNKNOWN=404,
	TOKEN_PIPE=101,
	TOKEN_DOUBLE_QUOTES=100,
	TOKEN_SINGLE_QUOTES=100,
	TOKEN_SINGLE_REDIR=101,
	TOKEN_DOUBLE_REDIR=101
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
}		t_list;

// linkedList.c file 
t_node	*create_node(char *data, t_token_type type);
void	init_list(t_list *list);
void	append(t_list *list, char *data, t_token_type type);
void	print_list(t_list *list);

// lexer.c file
t_token_type	get_char_type(char c);
t_list	*tokenize(const char *s);


#endif
