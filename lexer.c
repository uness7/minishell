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

int	lexer_build(char *input, size_t size, t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return -1;
	
	if (size == 0) {
		lexerbuf->ntoks = 0;
		return 0;
	}
	
	lexerbuf->llisttok = malloc(sizeof(t_tok));
	
	t_tok *token = lexerbuf->llisttok;
	tok_init(token, size);
	
	int i = 0;
	int j = 0, ntemptok = 0;
	
	char c;
	int state = STATE_GENERAL;
	
	do
	{
		c = input[i];		
		int chtype = getchartype(c);
		
		if (state == STATE_GENERAL)
		{
			switch (chtype) 
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
					token->data[j++] = c;
					token->type = TOKEN;
					break;
					
				case CHAR_WHITESPACE:
					if (j > 0) {
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
					token->data[0] = chtype;
					token->data[1] = 0;
					token->type = chtype;
					
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
					break;
			}
		}
		else if (state == STATE_IN_DQUOTE) {
			token->data[j++] = c;
			if (chtype == CHAR_DQUOTE)
				state = STATE_GENERAL;
			
		}
		else if (state == STATE_IN_QUOTE) {
			token->data[j++] = c;
			if (chtype == CHAR_QOUTE)
				state = STATE_GENERAL;
		}
		
		if (chtype == CHAR_NULL) {
			if (j > 0) {
				token->data[j] = 0;
				ntemptok++;
				j = 0;
			}
		}
		
		i++;
	} while (c != '\0');
	
	token = lexerbuf->llisttok;
	int k = 0;
	while (token != NULL) 
	{
		if (token->type == TOKEN)
		{
			glob_t globbuf;
			glob(token->data, GLOB_TILDE, NULL, &globbuf);
			
			if (globbuf.gl_pathc > 0)
			{
				k += globbuf.gl_pathc;
				// save the next token so we can attach it later
				t_tok *saved = token->next;
				
				// replace the current token with the first one
				free(token->data);
				token->data = malloc(strlen(globbuf.gl_pathv[0]) + 1);
				strcpy(token->data, globbuf.gl_pathv[0]);
								
				int i;
				for (i = 1; i < globbuf.gl_pathc; i++)
				{
					token->next = malloc(sizeof(t_tok));
					tok_init(token->next, strlen(globbuf.gl_pathv[i]));
					token = token->next;
					token->type = TOKEN;
					strcpy(token->data, globbuf.gl_pathv[i]);
				}
				token->next = saved;
			}
			else {
				// token from the user might be inside quotation to escape special characters
				// hence strip the quotation symbol
				char* stripped = malloc(strlen(token->data) + 1);
				strip_quotes(token->data, stripped);
				free(token->data);
				token->data = stripped;
				k++;
			}
		}
		token = token->next;
	}
	lexerbuf->ntoks = k;
	return k;
}

void lexer_destroy(t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return;
	
	tok_destroy(lexerbuf->llisttok);
}
