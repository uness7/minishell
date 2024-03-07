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

void	tokenize(char *input, size_t size, t_tok *token)
{
	int		i;
	int		j;
	int		state;
	int		ntemptok;
	char	c;
	int		chtype;

	i = 0;
	j = 0;
	state = STATE_GENERAL;
	ntemptok = 0;
	while (input[i] != '\0')
	{
		chtype = getchartype(input[i]);
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QOUTE)
			{
				state = STATE_IN_QUOTE;
				token->data[j++] = CHAR_QOUTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				token->data[j++] = CHAR_DQUOTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_ESCAPESEQUENCE)
			{
				token->data[j++] = input[++i];
				token->type = TOKEN;
			}
			else if (chtype == CHAR_GENERAL)
			{
				token->data[j++] = input[i];
				token->type = TOKEN;
			}
			else if (chtype == CHAR_WHITESPACE)
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
			else if (chtype == CHAR_SEMICOLON || chtype == CHAR_GREATER
				|| chtype == CHAR_LESSER || chtype == CHAR_AMPERSAND
				|| chtype == CHAR_PIPE)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				token->data[0] = chtype;
				token->data[1] = 0;
				token->type = chtype;
				token->next = malloc(sizeof(t_tok));
				token = token->next;
				tok_init(token, size - i);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = input[i];
			if (chtype == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = input[i];
			if (chtype == CHAR_QOUTE)
				state = STATE_GENERAL;
		}
		if (chtype == CHAR_NULL)
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
}

void	lexer_build(char *input, size_t size, t_lexer *lexerbuf)
{
	t_tok	*token;

	if (lexerbuf == NULL)
		return ;
	if (size == 0)
		return ;
	lexerbuf->llisttok = malloc(sizeof(t_tok));
	token = lexerbuf->llisttok;
	tok_init(token, size);
	tokenize(input, size, token);
	return ;
}

void lexer_destroy(t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return;
	tok_destroy(lexerbuf->llisttok);
}
