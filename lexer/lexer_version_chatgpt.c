

t_list	*tokenize(const char *input_str)
{
	char	current_char;
	char	current_token[1024] = "";
	int		in_quotes;
	int		i;

	in_quotes = 0;
	i = 0;
	while (input_str[i] != '\0')
	{
		current_char = input_str[i];
		if (current_char == ' ' && !in_quotes)
		{
			if (strlen(current_token) > 0)
			{
				printf("%s\n", current_token);
				strcpy(current_token, "");
			}
		}
		else if (current_char == '\'' || current_char == '"')
		{
			if (in_quotes && input_str[i - 1] == '\\')
				strncat(current_token, &current_char, 1);
			else
				in_quotes = !in_quotes;
		}
		else if (current_char == '\\' && input_str[i + 1] != '\0')
		{
			i++;
			strncat(current_token, &input_str[i], 1);
		}
		else
			strncat(current_token, &current_char, 1);
		i++;
	}
	if (strlen(current_token) > 0)
		printf("%s\n", current_token);
}
