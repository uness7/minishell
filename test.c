#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 50

// Function to check if a character is a delimiter
bool is_delimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<' || c == '>');
}

// Function to tokenize a string
int tokenize(const char *input, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH]) {
    int token_count = 0;
    int token_length = 0;

    // Iterate through each character in the input string
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        // If current character is not a delimiter and not null terminator
        if (!is_delimiter(c) && c != '\0') {
            // Add character to current token
            tokens[token_count][token_length++] = c;
        } else if (token_length > 0) { // If token is not empty
            // Null-terminate current token
            tokens[token_count++][token_length] = '\0';
            token_length = 0;

            // Check for special characters and add them as separate tokens
            if (c == '|' || c == '<' || c == '>') {
                tokens[token_count][0] = c;
                tokens[token_count++][1] = '\0';
            }
        }
        
        // Break if maximum number of tokens reached
        if (token_count >= MAX_TOKENS) {
            break;
        }
    }

    // If last token is not empty, increment token count
    if (token_length > 0) {
        tokens[token_count++][token_length] = '\0';
    }

    return token_count;
}

int main() {
    const char *input = "";
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];

    // Tokenize input string
    int token_count = tokenize(input, tokens);

    // Print tokens
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%s\n", tokens[i]);
    }

    return 0;
}

