/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 16:45:32 by yzioual          ###   ########.fr       */
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
		if (!ft_isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

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
			if (*s && *(s + 1) == *s)
			{
				token[i++] = *s++;
			}
			token[i] = '\0';
			append(list, token,
				(*s == '>') ? TOKEN_SINGLE_REDIR : TOKEN_DOUBLE_REDIR);
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
			if (quote == '\'')
				append(list, token, TOKEN_SINGLE_QUOTES);
			else
				append(list, token, TOKEN_DOUBLE_QUOTES);
		}
	}
	return (list);
}

int	main(void)
{
	const char	*str1 = "ls -l -al -d";
	const char	*str2 = "awl '{print $2}'";
	const char	*str3 = "ps | wc -l > test.txt";


	printf("Absract Syntax Tree\n");
	print_tree(parse(tokenize(str1)), 0);

	/*
	print_list(tokenize("echo Hello World | >>"));
	printf("\n");

	print_list(tokenize("ls | grep .txt"));
	printf("\n");
	print_list(tokenize(str1));
	printf("\n");
	print_list(tokenize(str2));
	printf("\n");
	print_list(tokenize(str3));
	printf("\n");
	print_list(tokenize("echo; '{hello wolrd $3}' >> ji "));
	printf("\n");
	print_list(tokenize("    "));
	printf("\n");
	print_list(tokenize(""));
	printf("\n");
	print_list(tokenize("ls -@ /"));
	printf("\n");
	print_list(tokenize("echo Hello\\ World"));
	printf("\n");
	print_list(tokenize("echo $PATH"));
	printf("\n");
	print_list(tokenize("echo hello*world"));
	printf("\n");
	print_list(tokenize("echo $HOME"));
	printf("\n");
	print_list(tokenize("echo hello\" world"));
	printf("\n");
	*/
}
