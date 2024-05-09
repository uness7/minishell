#include "minishell.h"

bool	is_quotes(char c)
{
	return (c == '"' || c == '\'');
}

void	remove_last_quote(char *str)
{
	int		len;
	bool	escaped;

	len = strlen(str);
	if (len == 0)
		return ;
	if (str[len - 1] == '"' || str[len - 1] == '\'')
	{
		escaped = false;
		int i = len - 2;
		while (i >= 0 && str[i] == '\\')
		{
			escaped = !escaped;
			i--;
		}
		if (!escaped)
			str[len - 1] = '\0';
	}
}

t_echo_arr	**split(t_arena *arena, char *input)
{
	t_echo_arr	**res;
	int			i;
	int			k;
	bool		inside_quotes;
	int			start_index;
	int			token_length;

	inside_quotes = false;
	res = arena_alloc(arena, (strlen(input)) * (sizeof(t_echo_arr *)) + 1);
	k = 0;
	i = 0;
	input+=5;
	while (input[i] != '\0')
	{
		if (is_quotes(input[i]))
		{
			inside_quotes = !inside_quotes;
			i++;
		}
		else if (!inside_quotes && is_space(input[i]))
		{
			res[k] = arena_alloc(arena, sizeof(t_echo_arr));
			res[k]->data = ft_strdup(arena, "SPACE");
			res[k]->type = _SPACE;
			k++;
			while (input[i] && input[i] == ' ')
				i++;
		}
		else
		{
			start_index = i;
			while (input[i] && (inside_quotes || input[i] != ' '))
			{
				if (input[i] == '"' || input[i] == '\'')
				{
					i++;
					inside_quotes = !inside_quotes;
					break ;
				}
				i++;
			}
			//printf("i : %d\n", i);
			if (start_index <= (int)strlen(input))
			{
				//printf("current : %c\n", input[i]);
				token_length = i - start_index;
				res[k] = arena_alloc(arena, sizeof(t_echo_arr));
				res[k]->data = arena_alloc(arena, (token_length + 1)
						* sizeof(char));
				res[k]->type = WORD;
				strncpy(res[k]->data, input + start_index, token_length);
				remove_last_quote(res[k]->data);
				res[k]->data[token_length] = '\0';
				k++;
			}
		}
	}
	k++;
	res[k] = NULL;
	return (res);
}
