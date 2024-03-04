#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to match a simple regex pattern against an input string
bool	match(const char *pattern, const char *input)
{
	while (*pattern && *input)
	{
		if (*pattern == *input || *pattern == '.')
		{
			pattern++;
			input++;
		}
		else if (*pattern == '*')
		{
			// Handle '*' as a wildcard
			pattern++;
		}
		else
		{
			return (false); // No match
		}
	}
	return (*pattern == '\0'); // Match if pattern is fully consumed
}

// Function to tokenize input string based on simple regex patterns
struct Token	tokenize(const char *input)
{
	const char	*end = input;
	int			length;
	char		*command;

	const char *prompt_pattern = "^\\$\\s";     // Match shell prompt
	const char *command_pattern = "^[a-zA-Z]+"; // Match command names
	// Add more patterns for other token types
	// Tokenize input
	if (match(prompt_pattern, input))
	{
		return ((struct Token){PROMPT, "$"});
	}
	else if (match(command_pattern, input))
	{
		// Extract command name
		while (*end && (*end == '_' || (*end >= 'a' && *end <= 'z')
				|| (*end >= 'A' && *end <= 'Z')))
		{
			end++;
		}
		length = end - input;
		command = malloc(length + 1);
		strncpy(command, input, length);
		command[length] = '\0';
		return ((struct Token){COMMAND, command});
	}
	else
	{
		return ((struct Token){-1, NULL}); // Invalid token
	}
}

int	main(void)
{
	struct Token	token;

	const char *input = "ls -l"; // Example input string
	printf("Input: %s\n", input);
	token = tokenize(input);
	if (token.type == PROMPT)
	{
		printf("Token: PROMPT, Value: %s\n", token.value);
	}
	else if (token.type == COMMAND)
	{
		printf("Token: COMMAND, Value: %s\n", token.value);
	}
	else
	{
		printf("Unrecognized token\n");
	}
	return (0);
}
