/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hichame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:37:59 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/03/22 17:00:55 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_pipe(const char *s, char *token, t_list *list)
{
    int i = 0;

    token[i++] = *s++;
    token[i] = '\0';
    append(list, token, TOKEN_PIPE);
}

void check_dir(char *s, char *token, t_list *list)
{
    int i = 0;
    char type;
    char type2;

    token[i++] = *s;
    type = *s;
    if (*s && *(s + 1) == *s)
    {
        type2 = *s;
        token[i++] = *s++;  
        token[i] = '\0';
        if (type2 == '<')
            append(list, token, TOKEN_REDIR_HEREDOC);
        else
            append(list, token, TOKEN_REDIR_APPEND);
    }
    else
    {
        token[i] = '\0';
        if (type == '>')
            append(list, token, TOKEN_REDIR_OUT);
        else
            append(list, token, TOKEN_REDIR_IN);
    }
}

void check_quote(char *s, char *token, t_list *list)
{
    int i = 0;
    char quote;

    quote = *s++;
    token[i++] = quote;
    while (*s != '\0' && *s != quote)
        token[i++] = *s++;
    if (*s == quote)
        token[i++] = *s++;
    token[i] = '\0';
    append(list, token, TOKEN_WORD);
}

t_list *tokenize(char *s)
{
    t_list *list;
    char *token;
    int i;

    list = malloc(sizeof(t_list));
    if (list == NULL || s == NULL)
        return (NULL);
    init_list(list);
    while (*s != '\0')
    {
        while (*s == ' ')
            s++;
        token = malloc(sizeof(char) * 1024);
        if (token == NULL)
            return (NULL);
	i = 0;
        if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0'
            && *s <= '9') || *s == '_' || *s == '-' || *s == '/'
            || *s == '$' || *s == '(' || *s == ')' || *s == '.')
	{
		while (*s && *s != ' ')
			token[i++] = *s++;
		token[i] = '\0';
		append(list, token, TOKEN_WORD);
	}
        else if (*s == '|')
	{
		check_pipe(s, token, list);
		s++;
	}
        else if (*s == '>' || *s == '<')
	{
            check_dir(s, token, list);
	    s++;
	}
        else if (*s == '\'' || *s == '\"')
            check_quote(s, token, list);
    }
    return (list);
}

int main()
{
	print_list(tokenize("ls -al | wc -l >> test.txt"));
}
