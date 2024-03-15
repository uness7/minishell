/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:20 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/14 16:35:40 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_char_type
{
	GENERAL,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	PIPE,
	GREATER,
	LESSER,
}		t_char_type;

typedef enum e_token_type
{
	TOKEN=100,
	TOKEN_UNKNOWN=-1,
	TOKEN_PIPE=101,
	TOKEN_DOUBLE_QUOTES=102,
	TOKEN_SINGLE_QUOTES=103,
	TOKEN_SINGLE_REDIR=104,
	TOKEN_DOUBLE_REDIR=105
}		t_token_type;

typedef struct s_node
{
	char		*data;
	t_token_type	type;
	struct s_node	*next;
}		t_node;

typedef struct s_list
{
	t_node	*head;
}		t_list;

// linkedList.c file
t_node	*create_node(char *data, t_token_type type);
void	init_list(t_list *list);
void	append(t_list *list, char *data, t_token_type type);
void	print_list(t_list *list);

// lexer.c file
t_token_type	get_char_type(char c);
t_list	*tokenize(const char *s);

#endif
