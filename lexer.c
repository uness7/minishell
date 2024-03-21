/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/18 17:38:58 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_special_chars(const char **s, t_list **list)
{
	if (**s == '>')
	{
		if (*(*s + 1) == '>')
		{
			append(*list, strdup(">>"), TOKEN_REDIR_APPEND);
			(*s)++;
		}
		else
			append(*list, strdup(">"), TOKEN_REDIR_OUT);
	}
	else if (**s == '<')
	{
		if (*(*s + 1) == '<')
		{
			append(*list, strdup("<<"), TOKEN_REDIR_HEREDOC);
			(*s)++;
		}
		else
			append(*list, strdup("<"), TOKEN_REDIR_IN);
	}
	else if (**s == '|')
		append(*list, strdup("|"), TOKEN_PIPE);
	(*s)++;
}


void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

void	add_word_token_if_valid(const char **start, const char **input, t_list **tokens)
{
	char	*word;

	if (*input > *start)
	{
		word = strndup(*start, *input - *start);
		if (word)
			append(*tokens, word, TOKEN_WORD);
		else
		{
			printf("Error: Malloc failed in handle_word.\n");
			exit(0);
		}
	}
}

void	handle_words(const char **input, t_list **tokens)
{
	const char	*start;
	int	in_quote;
	char	quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(&start, input, tokens);
}


t_list	*tokenize(const char *s)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
	{
		printf("Error allocating memory\n");
		return (0);
	}
	init_list(list);
	while (*s)
	{
		while (*s && strchr(" \t\n", *s))
			s++;
		if (strchr("><|", *s))
			handle_special_chars(&s, &list);
		else
			handle_words(&s, &list);
		s++;
	}
	return (list);
}

/*
int	main()
{
	print_list(tokenize("ls -a -l | wc -l >> test.txt"));
	return 0;
}
*/
