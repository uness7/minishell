#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}


int	ft_comma(char *s)
{
	char	curr;
	int	i = 0;

	if (ft_strlen(s) == 0)
		return 0;
	while (*s)
	{
		if (*s && *s != )
			i++;			
		s++;
	}
	return (i);
}



int main() {
    char *test_cases[] = {
        "abcABC",      // Expected: 0 (no differences of 32 ASCII units)
        "aabbcc",      // Expected: 0 (no differences of 32 ASCII units)
        "aAbBcC",      // Expected: 3 (each lowercase letter followed by its corresponding uppercase letter)
        "aAbcBcCdDeE", // Expected: 5 (aA, bB, cC, dD, eE)
        "abc",         // Expected: 0 (no uppercase letters to compare)
        "",            // Expected: 0 (empty string)
        NULL           // End of test cases
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test case %d: \"%s\" --> %d\n", i+1, test_cases[i], ft_comma(test_cases[i]));
    }

    return 0;
}

