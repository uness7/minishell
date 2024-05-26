/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/04/19 11:11:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

static void	add_word_token_if_valid(t_arena *arena, const char **start,
		const char **input, t_list **tokens)
{
	char	*word;

	word = NULL;
	if (*input > *start)
	{
		word = ft_strndup(arena, *start, *input - *start);
		if (word)
		{
			append(arena, *tokens, word, TOKEN_WORD);
		}
		else
		{
			printf("Error: Malloc failed in handle_word.\n");
			exit(0);
		}
	}
}

static void	handle_words(t_arena *arena, const char **input, t_list **tokens)
{
	const char	*start;
	int			in_quote;
	char		quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(arena, &start, input, tokens);
}

t_list	*tokenize(t_arena *arena, const char *s)
{
	t_list	*list;

	list = arena_alloc(arena, sizeof(t_list));
	init_list(list);
	while (*s)
	{
		while (*s && ft_strchr(" \t\n", *s))
			s++;
		if (ft_strchr("><|", *s))
			handle_special_chars(arena, &s, &list);
		else
			handle_words(arena, &s, &list);
	}
	return (list);
}
