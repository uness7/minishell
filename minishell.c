#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		printf("Input: %s\n", input);
		print_tree(parse(tokenize(input)), 0);
		free(input);
	}
	return (0);
}
