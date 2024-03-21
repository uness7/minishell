#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	tokenize_input(const char *input_str)
{
	char	current_char;

	char current_token[1024] = ""; // Current token being constructed
	int in_quotes = 0;             // Flag to track if currently inside quotes
	int i = 0;                     // Index for iterating over input string
	// Iterate over each character in the input string
	while (input_str[i] != '\0')
	{
		current_char = input_str[i];
		// Handling spaces
		if (current_char == ' ' && !in_quotes)
		{
			if (strlen(current_token) > 0)
			{
				printf("%s\n", current_token); // Print current token
				strcpy(current_token, "");     // Reset current token
			}
		}
		// Handling quotes
		else if (current_char == '\'' || current_char == '"')
		{
			if (in_quotes && input_str[i - 1] == '\\')
			{
				// Handle escaped quotes inside quoted strings
				strncat(current_token, &current_char, 1);
			}
			else
			{
				in_quotes = !in_quotes; // Toggle quoted mode
			}
		}
		// Handling escape characters
		else if (current_char == '\\' && input_str[i + 1] != '\0')
		{
			// Skip the special processing for the next character
			i++;
			strncat(current_token, &input_str[i], 1);
		}
		else
		{
			strncat(current_token, &current_char, 1);
				// Add character to current token
		}
		i++; // Move to the next character
	}
	// Print the last token if it's not empty
	if (strlen(current_token) > 0)
	{
		printf("%s\n", current_token);
	}
}

int	main(int ac, char **av)
{
	tokenize_input(av[1]);
	printf("\n");
	return (0);
}
