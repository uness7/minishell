#include "lexer.h"

int	main(int argc, char **argv)
{
	char	*input_string = argv[1];
	t_tok	*token;
	t_lexer lexerbuf;

	lexer_build(input_string, strlen(input_string), &lexerbuf);
	token = lexerbuf.llisttok;
	printf("Tokens:\n");
	while (token != NULL)
	{
		printf("Type: %d, Data: %s\n", token->type, token->data);
		token = token->next;
	}
	lexer_destroy(&lexerbuf);
	return 0;
}

