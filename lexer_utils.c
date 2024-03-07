/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:46:30 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/07 12:22:37 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
   -   state, ntemptok, chtype, i and j are part of obj
   */


void	handle_new_token(t_tok *token, t_obj obj, size)
{
	if (obj.j > 0)
	{
		token->data[obj.j] = 0;
		token->next = malloc(sizeof(t_tok));
		token = token->next;
		tok_init(token, size - obj.i);
		j = 0;
	}
}

void	handle_new_operator_token(t_tok *token, t_obj obj, size)
{
	if (obj.j > 0)
	{
		token->data[obj.j] = 0;
		token->next = malloc(sizeof(t_tok));
		token = token->next;
		tok_init(token, size - obj.i);
		obj.j = 0;
	}
	token->data[0] = chtype;
	token->data[1] = 0;
	token->type = TOKEN;
	token->next = malloc(sizeof(t_tok));
	token = token->next;
	tok_init(token, size - i);
}

void	handle_general_state(t_tok *token, t_obj obj, char *input)
{
	if (chtype == CHAR_QOUTE)
	{
		state = STATE_IN_QUOTE;
		token->data[j++] = CHAR_QOUTE;
		token->type = TOKEN;
	}
	else if (chtype == CHAR_DQUOTE)
	{
		state = STATE_IN_DQUOTE;
		token->data[j++] = CHAR_DQUOTE;
		token->type = TOKEN;
	}
	else if (chtype == CHAR_ESCAPESEQUENCE)
	{
		token->data[j++] = input[++i];
		token->type = TOKEN;
	}
	else if (chtype == CHAR_GENERAL)
	{
		token->data[j++] = input[i];
		token->type = TOKEN;
	}
	else if (chtype == CHAR_WHITESPACE)
		handle_new_token();
	else if (chtype == CHAR_GREATER || chtype == CHAR_LESSER || chtype == CHAR_AMPERSAND || chtype == CHAR_PIPE)
		handle_new_operator_token();
}

void	handle_in_quote_states(t_tok *token, t_obj obj, char *input)
{
	token->data[obj.j++] = input[obj.i];
	if (obj.chtype == CHAR_QOUTE || obj.chtype == CHAR_DQUOTE)
		obj.state = STATE_GENERAL;
}

void	tokenize(char *input, size_t size, t_tok *token, t_obj obj)
{
	obj.i = 0;
	obj.j = 0;
	obj.ntemptok = 0;
	obj.state = STATE_GENERAL;
	while (input[obj.i] != '\0')
	{
		obj.chtype = getchartype(input[obj.i]);

		if (obj.state == STATE_GENERAL)
			handle_general_state(token, obj, input);
		else if (obj.state == STATE_IN_QUOTE || obj.state == STATE_IN_DQOUTE)
			handle_in_quote_states(token, obj, input);

		if (obj.chtype == CHAR_NULL)
                {
                        if (obj.j > 0)
                        {
                                token->data[obj.j] = 0;
                                obj.ntemptok++;
                                obj.j = 0;
                        }
                }
                obj.i++;
	}
}
