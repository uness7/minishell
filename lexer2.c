/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 17:38:58 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenize(const char *s)
{
	t_list	*list;
	int		i;
	char	*token;
	char	quote;

	list = malloc(sizeof(t_list));
	if (list == NULL)
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
			token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN_PIPE);
		}
		else if (*s == '>' || *s == '<')
		{
			token[i++] = *s;
			char type = *s;
			if (*s && *(s + 1) == *s)
			{
				char type = *s;
				token[i++] = *s++;
				token[i] = '\0';
				if (type == '>')
					append(list, token, TOKEN_REDIR_APPEND);
				else
					append(list, token, TOKEN_REDIR_HEREDOC);
				s++;
			}
			token[i] = '\0';
			if (type == '>')
				append(list, token, TOKEN_REDIR_IN); 
			else
				append(list, token, TOKEN_REDIR_OUT); 
			s++;
		}
		else if (*s == '\'' || *s == '\"')
		{
			quote = *s++;
			token[i++] = quote;
			while (*s != '\0' && *s != quote)
			{
				token[i++] = *s++;
			}
			if (*s == quote)
				token[i++] = *s++;
			token[i] = '\0';
			append(list, token, TOKEN_WORD);
		}
	}
	return (list);
}

