#include "lexer.h"

t_token	*tokenize(const char *s)
{
	t_token	*list;
	char	current;
	
	list = NULL;
	
	while (*s)
	{
		current = *s;
		if (get_char_type(current) == '|')
	}
	return (list);
}
