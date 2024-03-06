#include "lexer.h"

int	getchartype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == 't')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '0')
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

void	strip_quotes(char *src, char *dest)
{
	int	i;
	int	n = strlen(src);
	char lastquote = 0;
	int j = 0;

	if (n <= 1)
	{
		strcpy(dest, src);
		return;
	}
	for (i=0; i < n; i++)
	{
		char c = src[i];
		if ((c == '\'' || c == '\"') && lastquote == 0)
			lastquote = c;
		else if (c == lastquote)
			lastquote = 0;
		else
			dest[j++] = c;
	}
	
	dest[j] = 0;
}

void	tok_init(t_tok *tok, int datasize)
{
	tok->data = malloc(datasize + 1); 
	tok->data[0] = 0;
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

void tok_destroy(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

/*
void    ft_tokenize(size_t size, char *input, int i, int j, int char_type, t_tok *token, int *state)
{
        if (char_type == CHAR_DQUOTE)
        {
                *state = STATE_IN_DQUOTE;
                token->data[j++] = CHAR_DQUOTE;
                token->type = TOKEN;
        }
        else if (char_type == CHAR_QOUTE)
        {
                *state = STATE_IN_QUOTE;
                token->data[j++] = CHAR_QOUTE;
                token->type = TOKEN;
        }
        else if (char_type == CHAR_ESCAPESEQUENCE)
        {
                token->data[j++] = input[++i];
                token->type = TOKEN;
        }
        else if (char_type == CHAR_GENERAL)
        {
                token->data[j++] = input[i];
                token->type = TOKEN;
        }
        else if (char_type == CHAR_WHITESPACE)
        {
                if (j > 0)
                {
                        token->data[j] = 0;
                        token->next = malloc(sizeof(t_tok));
                        token = token->next;
                        tok_init(token, size - i);
                        j = 0;
                }
        }
        else if (char_type == CHAR_SEMICOLON || char_type == CHAR_GREATER || \
                        char_type == CHAR_LESSER || char_type == CHAR_AMPERSAND || char_type == CHAR_PIPE)
        {
                if (j > 0)
                {
                        token->data[j] = 0;
                        token->next = malloc(sizeof(t_tok));
                        token = token->next;
                        tok_init(token, size - i);
                        j = 0;
                }
                token->data[0] = char_type;
                token->data[1] = 0;
                token->type = char_type;
                token->next = malloc(sizeof(t_tok));
                tok_init(token, size - i);
        }
}
*/

void	lexer_build(char *input, size_t size, t_lexer *lexerbuf)
{
	int	i = 0;
	int	j = 0;
	int	ntemptok = 0;
	int	char_type;
	t_tok	*token;
	int	state;
	
	
	state = STATE_GENERAL;
	if (lexerbuf == NULL)
		return ;
	if (size == 0)
	{
		lexerbuf->ntoks = 0;
		return ;
	}
	lexerbuf->llisttok = malloc(sizeof(t_tok));
	token = lexerbuf->llisttok;
	tok_init(token, size);
	/*
	while (input[i])
	{
		char_type = getchartype(input[i]);
		if (state == STATE_GENERAL)
		{
			ft_tokenize(size, input, i, j, char_type, token, &state);
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = input[i];
                        if (char_type == CHAR_DQUOTE)
                                state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = input[i];
                        if (char_type == CHAR_QOUTE)
                                state = STATE_GENERAL;
		}
		if (char_type == CHAR_NULL)
                {
                        if (j > 0)
                        {
                                token->data[j] = 0;
                                ntemptok++;
                                j = 0;
                        }
                }
		i++;
	}
	*/
	while (input[i] != '\0')
	{
		char_type = getchartype(input[i]);
		if (state == STATE_GENERAL)
		{
			switch (char_type) 
			{
				case CHAR_QOUTE:
					state = STATE_IN_QUOTE;
					token->data[j++] = CHAR_QOUTE;
					token->type = TOKEN;
					break;
				case CHAR_DQUOTE:
					state = STATE_IN_DQUOTE;
					token->data[j++] = CHAR_DQUOTE;
					token->type = TOKEN;
					break;
				case CHAR_ESCAPESEQUENCE:
					token->data[j++] = input[++i];
					token->type = TOKEN;
					break;
				case CHAR_GENERAL:
					token->data[j++] = input[i];
					token->type = TOKEN;
					break;
				case CHAR_WHITESPACE:
					if (j > 0)
					{
						token->data[j] = 0;
						token->next = malloc(sizeof(t_tok));
						token = token->next;
						tok_init(token, size - i);
						j = 0;
					}
					break;
				case CHAR_SEMICOLON:
				case CHAR_GREATER:
				case CHAR_LESSER:
				case CHAR_AMPERSAND:
				case CHAR_PIPE:
					// end the token that was being read before
					if (j > 0) {
						token->data[j] = 0;
						token->next = malloc(sizeof(t_tok));
						token = token->next;
						tok_init(token, size - i);
						j = 0;
					}
					// next token
					token->data[0] = char_type;
					token->data[1] = 0;
					token->type = char_type;
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
					break;
			}
		}
		else if (state == STATE_IN_DQUOTE) {
			token->data[j++] = input[i];
			if (char_type == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE) {
			token->data[j++] = input[i];
			if (char_type == CHAR_QOUTE)
				state = STATE_GENERAL;
		}
		if (char_type == CHAR_NULL)
		{
			if (j > 0)
			{
				token->data[j] = 0;
				ntemptok++;
				j = 0;
			}
		}
		i++;
	}
	token = lexerbuf->llisttok;
}

void lexer_destroy(t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return;
	tok_destroy(lexerbuf->llisttok);
}
