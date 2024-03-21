#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/* Contains bugs */



bool	has_double_unclosed_quotes(const char *s)
{
	int	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\"')
			flag = !flag;
		s++;
	}
	return (flag);
}
bool	has_single_unclosed_quotes(const char *s)
{
	int	flag;

	flag = false;
	while (*s)
	{
		if (*s == '\'')
			flag = !flag;
		s++;
	}
	return (flag);
}

bool	has_logical_ops(const char *s)
{
	while (*s)
	{
		if ((*s == '&' && *(s + 1) == '&') || (*s == '|' && *(s + 1) == '|'))
			return (true);
		s++;
	}
	return (false);
}

/*
bool	has_misplaced_ops(const char *s)
{
	bool	last_op;
	bool	in_quotes;

	last_op = false;
	in_quotes = false;
	if (*s == '>' || *s == '<' || *s == '|')
		return (true);
	s++;
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			in_quotes = !in_quotes;
		else if (!in_quotes)
		{
			if (*s == '>' || *s == '|' || *s == '<')
				if (last_op == true)
					return (true);
			last_op = true;
		}
		else
			last_op = false;
		s++;
	}
	return (false);
}
*/

#include <stdbool.h>

bool	has_misplaced_ops(const char *s)
{
	bool	valid_command;
	bool	in_quotes;

	valid_command = true;
	in_quotes = false;
	bool last_op = false; // Tracks if the last character was an operator
	while (*s && *s == ' ')
		s++;
	if (*s == '>' || *s == '<' || *s == '|')
		return (true);
	while (*s)
	{
		if (*s == '\"')
		{
			in_quotes = !in_quotes; // Toggle in_quotes when encountering quotes
		}
		else if (!in_quotes)
		{
			if (*s == '>' || *s == '<' || *s == '|')
			{
				if (last_op)
				{
					valid_command = false; // Two operators in a row,
						command is invalid
					break ;
				}
				last_op = true; // Mark current character as an operator
			}
			else
			{
				last_op = false; // Mark current character as not an operator
			}
		}
		s++;
	}
	if (*(s - 1) == '>' || *(s - 1) == '<' || *(s - 1) == '|')
		return (true);
	return (!valid_command); // Return true if the command is not valid
}

bool	is_input_valid(const char *s)
{
	return (!(has_double_unclosed_quotes(s) || has_misplaced_ops(s)
			|| has_logical_ops(s) || has_single_unclosed_quotes(s)));
}

int	main(void)
{
	const char	*s = "ls -l | hello  | > d";

	if (is_input_valid(s) == true)
		printf("valid");
	else
		printf("not valid");
}
