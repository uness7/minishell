/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hichame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenaddi <hbenaddi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:37:59 by hbenaddi          #+#    #+#             */
/*   Updated: 2024/03/22 14:40:40 by hbenaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_is_print(char *s, char *token, t_list *list)
{
    int i = 0;

    while (*s != '\0' && *s != ' ')
    {
        token[i++] = *s;
        s++;
    }
    token[i] = '\0';
    append(list, token, TOKEN);
}


void check_pipe(const char *s, char *token, t_list *list)
{
    int i = 0;

    token[i++] = *s++;
    token[i] = '\0';
    append(list, token, TOKEN_PIPE);
}

void check_dir(const char *s, char *token, t_list *list)
{
	int i = 0;
	int type_token;

	token[i++] = *s;
	if (*s && *(s + 1) == *s)
	{
		token[i++] = *s++;
		type_token = TOKEN_DOUBLE_REDIR;
	}
	else
	{
		type_token = TOKEN_SINGLE_REDIR;
		if (*s && *(s + 1) != *s)
			s++;
	}
	token[i] = '\0';
	append(list, token, type_token);
}

void check_quote(char *s, char *token, t_list *list)
{
	int i = 0;
	char quote;

	quote = *s++;
	token[i++] = quote;
	while (*s != '\0' && *s != quote) 
	{
		token[i++] = *s++;
	}
	if (*s == quote)
		token[i++] = *s++;
	token[i] = '\0';
	if (quote == '\'')
		append(list, token, TOKEN_SINGLE_QUOTES);
	else
		append(list, token, TOKEN_DOUBLE_QUOTES);
}

t_list	*tokenize(char *s)
{
	t_list	*list;
	char	*token;

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
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0'
				&& *s <= '9') || *s == '_' || *s == '-' || *s == '/'
			|| *s == '$' || *s == '(' || *s == ')' || *s == '.')
			check_is_print(s, token, list);
		else if (*s == '|')
			check_pipe(s, token, list);
		else if (*s == '>' || *s == '<')
			check_dir(s, token, list);
		else if (*s == '\'' || *s == '\"')
			check_quote(s, token, list);
		s++;
	}
	return (list);
}
int main ()
{
	print_list(tokenize("test | test"));
}