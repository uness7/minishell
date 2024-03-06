
void	ft_tokenize(char c, int i, int j, int char_type, t_tok *token, int *state)
{
	if (char_type == CHAR_DQUOTE)
	{
		*state = STATE_IN_DQUOTE;
		token->data[j++] = CHAR_DQUOTE; 
		token->type = TOKEN;
		return ;
	}
	else if (char_type == CHAR_QUOTE)
	{
		*state = STATE_IN_QUOTE;
		token->data[j++] = CHAR_QUOTE;
		token->type = TOKEN;
		return ;
	}
	else if (char_type == CHAR_ESCAPESEQUENCE)
	{
		token->data[j++] = input[++i]; // to-add i, j
		token->type = TOKEN;
		return ;
	}
	else if (char_type == CHAR_GENERAL)
	{
		token->data[j++] = C; // to-add
		token->type = TOKEN;
		return ;
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
		return ;
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
		return ;
	}
	return ;
}

int	lexer(char *input, size_t size, t_lexer *buffer)
{
	int	i;
	int	j;
	int	ntemtok;
	int	char_type;
	int	state;
	t_tok	*token;

	i = 0;
	j = 0;
	ntemptol = 0;
	state = STATE_GENERAL;
	if (buffer == NULL) return (-1);
	if (size == 0)
	{
		buffer->ntoks = 0;
		return (0);
	}
	buffer->llisttok = malloc(sizeof(t_tok));
	token = buffer->llsittok;
	tok_init(token, size);
	while (input[i] != '\0')
	{
		char_type = getchartype(input[i]);
		if (state == STATE_GENERAL)
		{
			ft_tokenize(char_type, i, j, token, &state);
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = input[i];
			if (char_type == CHAR_DQUOTE)
			{
				state = STATE_GENERAL;
			}
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = input[i];
			if (char_type == CHAR_QUOTE)
			{
				state = STATE_GENERAL;
			}
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
				tok_t* saved = token->next;

				// replace the current token with the first one
				free(token->data);
				token->data = malloc(strlen(globbuf.gl_pathv[0]) + 1);
				strcpy(token->data, globbuf.gl_pathv[0]);

				int i;
				for (i = 1; i < globbuf.gl_pathc; i++)
				{
					token->next = malloc(sizeof(tok_t));
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
