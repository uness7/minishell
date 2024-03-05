#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main(int argc, char *argv[]) {

    char *input_string = argv[1];

    t_lexer lexerbuf;
    int num_tokens = lexer_build(input_string, strlen(input_string), &lexerbuf);
    
    t_tok *token = lexerbuf.llisttok;
    printf("Number of tokens: %d\n", num_tokens);
    printf("Tokens:\n");
    while (token != NULL) {
        printf("Type: %d, Data: %s\n", token->type, token->data);
        token = token->next;
    }

    // Destroy lexer buffer
    lexer_destroy(&lexerbuf);

    return 0;
}

