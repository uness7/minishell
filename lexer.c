#include "minishell.h"
#include <ctype.h>

t_token_type	get_char_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '\'')
		return (TOKEN_SINGLE_QUOTES);
	else if (c == '\"')
		return (TOKEN_DOUBLE_QUOTES);
	else if (c == '>')
		return (TOKEN_SINGLE_REDIR);
	else if (c == '<')
		return (TOKEN_SINGLE_REDIR);
	return (TOKEN);
}

t_list	*tokenize(const char *s)
{
	t_list	*list;
	int		i;
	char	*token;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	init_list(list);

	while (*s)
	{
		i = 0;
		token = malloc(sizeof(char) * 100);
		if (token == NULL)
			return NULL;

		// works
		/*
		if (*s == '|')
		{
			token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_PIPE);
		}
		// doesn't work
		else if (*s == '\'')
		{
			s++;
			while (*s && *s != '\'')
				token[i++] = *s++;
		}
		// doesn't work
		else if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')
				token[i++] = *s++;
		}
		// doesn't work
		else if (*s == '>') 
		{
			if (*(s+1) == '>')
			{
				token[i++] = '>';
				token[i++] = '>';
				token[i] = '\0';
				append(list, token, TOKEN_DOUBLE_REDIR);
			}
			token[i++] = '>';
			token[i] = '\0';
			append(list, token, TOKEN_SINGLE_REDIR);
		}
		
		*/
		if (*s != '|' && *s != '\'' && *s != '\"' && *s != '>' && *s != '<')
		{
			while (*s)
        			token[i++] = *s++;
		}
		token[i] = '\0';
		append(list, token, get_char_type(token[0]));
		s++;
	}
	return (list);
}

int main(int ac, char **av)
{
    print_list(tokenize(av[1]));
    return 0;
}
