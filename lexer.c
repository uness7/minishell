/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/14 17:18:47 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (*s != '\0')
	{
		token = malloc(sizeof(char) * 100);	
		if (token == NULL) return (NULL);

		i = 0;
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') && (*s >= '0' && *s <= '9'))
		{
			while (*s && *s != ' ')
				token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN);
		}
		else if (*s == '|')
		{
			token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_PIPE);
		}
		else if (*s == '>' || *s == '<')
		{
			if (*(s+1) != '>' && *(s+1) != '<')
			{
				token[i++] = *s;
				token[i] = '\0';
				append(list, token, TOKEN_SINGLE_REDIR);
			}
			else if (*(s+1) == '>' || *(s+1) == '<')
			{
				token[i++] = *s;
				token[i++] = *s;
				token[i] = '\0';
				append(list, token, TOKEN_DOUBLE_REDIR);
				s++;
			}
		}
		else if (*s == '\'')
		{
			//s++;
			token[i++] = *s++;
			while (*s && *s != '\'')
				token[i++] = *s++;
			if (*s == '\'')
				token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_SINGLE_QUOTES);
		}
		else if (*s == '\"')
		{
			token[i++] = *s++;
			while (*s && *s != '\"')
				token[i++] = *s++;
			if (*s == '\"')
				token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_DOUBLE_QUOTES);
		}
		s++;
	}

	return (list);
}

/*
int main(int ac, char **av)
{
    print_list(tokenize(av[1]));
    return 0;
}
*/


int main() {
    const char *test_cases[] = {
        "ls -l /",
        "echo 'Hello, World!'",
        "echo \"Hello, World!\"",
        "ls > output.txt",
        "ls | grep .txt",
        "  echo   Hello   World!   ",
        "echo $PATH",
        "echo (Hello)",
        "ls; echo 'Done'",
        "echo \"Hello\nWorld\"",
        "",
        "    "
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        printf("Test Case %d:\n", i + 1);
        printf("Input: \"%s\"\n", test_cases[i]);

        t_list *tokens = tokenize(test_cases[i]);
        if (tokens == NULL) {
            printf("Error: Memory allocation failed.\n");
        } else {
            printf("Tokens:\n");
            print_list(tokens);
        }
        printf("\n");
    }

    return 0;
}
