/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:21:41 by yzioual           #+#    #+#             */
/*   Updated: 2024/03/04 13:08:52 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_OF_TOKENS 100

char **ft_tokenize(char *av)
{
    char **tokens;
    char *current_token;
    bool inside_quotes = false;
    bool escaped = false;
    int i = 0;
    int j = 0;

    *tokens = malloc(sizeof(char *) * NUM_OF_TOKENS);
    if (tokens == NULL)
        return NULL;
    current_token = malloc(sizeof(char) * (strlen(av) + 1));
    if (current_token == NULL) {
        free(tokens);
        return NULL;
    }
    while (av[i])
    {
        if (av[i] == '\\' && !escaped) {
            escaped = true;
            current_token[j++] = av[i];
        } else if ((av[i] == '\'' || av[i] == '"') && !escaped) {
            inside_quotes = !inside_quotes;
            current_token[j++] = av[i];
        } else if (av[i] == ' ' && !escaped && !inside_quotes) {
            if (j > 0) {
                current_token[j] = '\0';
                tokens[i++] = strdup(current_token);
                j = 0;
            }
        } else {
            current_token[j++] = av[i];
            escaped = false;
        }
        i++;
    }
    if (j > 0) {
        current_token[j] = '\0';
        tokens[i++] = strdup(current_token);
    }
    tokens[i] = NULL;
    free(current_token);

    return tokens;
}

int main()
{
    char **tokens = ft_tokenize("hello");
    if (tokens == NULL) {
        printf("Tokenization failed\n");
        return 1;
    }
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}

