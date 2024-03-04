/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:29:04 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/04 10:34:51 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lexer */
typedef enum s_token_type
{
	CMD,
	ARG,
	OP
}		t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char		*data; // additional data, if needed
}		t_token;


#endif
