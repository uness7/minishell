#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool	scan(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '\'')
			count++;
		if (count == 2)
			return (true);
		s++;
	}
	return (false);
}




