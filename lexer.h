#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_token_type
{
	TOKEN,
	TOKEN_UNKNOWN,
	TOKEN_PIPE,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_SINGLE_QUOTES,
	TOKEN_SINGLE_REDIR,
	TOKEN_DOUBLE_REDIR
}		t_token_type;

typedef struct s_token
{
	char		*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

#endif
