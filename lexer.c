/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/15 15:35:44 by yzioual          ###   ########.fr       */
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

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_empty(const char *s)
{
	while (*s != '\0')
	{
		if (!ft_isspace((unsigned char) *s))
			return (0);
		s++;
	}
	return (1);
}

/*
t_list	*tokenize(const char *s)
{
	t_list	*list;
	int		i;
	char	*token;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	init_list(list);
	if (is_empty(s))
	{	
		printf("String is empty or has only whitespaces\n");
		exit(1);
	}
	while (*s != '\0')
	{
		token = malloc(sizeof(char) * 100);	
		if (token == NULL) return (NULL);

		printf("Processing input string: \"%s\"\n", s);
		i = 0;
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9') ||
				*s == '_' || *s == '-' || *s == '/' || *s == '$' || *s == '(' || *s == '(')
		{
			while (*s && *s != ' ')
				token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN);
		}
		else if (*s && *s == '|')
		{
			token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN_PIPE);
		}
		else if (*s && *s == '>' || *s == '<')
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
		else if (*s && *s == '\'')
		{
			//s++;
			token[i++] = *s++;
			while (*s && *s != '\'')
				token[i++] = *s++;
			if (*s == '\'')
				token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN);
		}
		else if (*s && *s == '\"')
		{
			token[i++] = *s++;
			while (*s && *s != '\"')
				token[i++] = *s++;
			if (*s == '\"')
				token[i++] = *s;
			token[i] = '\0';
			append(list, token, TOKEN);
		}
		s++;
	}
	//printf("Token: \"%s\", Type: %d\n", token, get_char_type(token[0]));
	free(token);
	return (list);
}

*/
/*
int main(int ac, char **av)
{
    print_list(tokenize(" "));
    return 0;
}
*/


t_list	*tokenize(const char *s)
{
    t_list *list;
    int    i;
    char   *token;

    list = malloc(sizeof(t_list));
    if (list == NULL)
        return (NULL);
    init_list(list);

    if (is_empty(s)) {
        printf("String is empty or has only whitespaces\n");
        free(list); // Avoid memory leak
        return NULL;
    }

    while (*s != '\0')
    {
        while (*s == ' ')
		s++;

        token = malloc(sizeof(char) * 1024); 
        if (token == NULL)
            return (NULL);

        printf("Processing input string: \"%s\"\n", s);
        i = 0;
        if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9') ||
            *s == '_' || *s == '-' || *s == '/' || *s == '$' || *s == '(' || *s == ')') { // Corrected duplicated '('
            while (*s && *s != ' ')
                token[i++] = *s++;
            token[i] = '\0';
            append(list, token, TOKEN);
        }
        else if (*s == '|')
	{
            token[i++] = *s++;
            token[i] = '\0';
            append(list, token, TOKEN_PIPE);
        }
        else if (*s == '>' || *s == '<')
	{
            token[i++] = *s;
            if (*s && *(s+1) == *s)
	    {
                token[i++] = *s++;
            }
            token[i] = '\0';
            append(list, token, (*s == '>') ? TOKEN_SINGLE_REDIR : TOKEN_DOUBLE_REDIR);
        }
        else if (*s == '\'' || *s == '\"') {
            char quote = *s++;
            token[i++] = quote;
            while (*s && *s != quote)
                token[i++] = *s++;
            if (*s == quote)
                token[i++] = *s++; // Increment s to move past the closing quote
            token[i] = '\0';
            append(list, token, (quote == '\'') ? TOKEN_SINGLE_QUOTES : TOKEN_DOUBLE_QUOTES);
        }
	// omitted else for unrecognized tokens
    }
    return (list);
}



int	main()
{
	const char	*str1 = "ls -al /";
	const char	*str2 = "awl '{print $2}'";
	const char	*str3 = "ps | wc -l > test.txt";


	print_list(tokenize(str1));
	print_list(tokenize(str2));
	print_list(tokenize(str3));
	print_list(tokenize("echo; '{hello wolrd >> $3}'"));
	
}
