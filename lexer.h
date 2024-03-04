#ifndef LEXER_H
#define LEXER_H

enum TokenType {
    PROMPT,
    HISTORY,
    EXECUTABLE,
    SIGNAL,
    QUOTED_STRING,
    REDIRECTION,
    PIPE,
    ENV_VARIABLE,
    SPECIAL_VARIABLE,
    BUILTIN
};

typedef struct s_token_type
{
	enum TokenType token_type;	
	char	*data;
}

#endif

