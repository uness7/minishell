#ifndef LEXER_H
#define LEXER_H

#include <glob.h>
#include <stdlib.h>
#include <string.h>

enum TokenType
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,	
	TOKEN = -1,
};

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef struct s_tok
{
	char		*data;
	int		type;
	struct s_tok 	*next;
}	t_tok;

typedef struct s_lexer
{
	t_tok *llisttok;
	int ntoks;
}	t_lexer;

int		lexer_build(char *input, size_t size, t_lexer *lexerbuf);
void	lexer_destroy(t_lexer *lexerbuf);

#endif
