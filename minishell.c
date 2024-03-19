#include "minishell.h"

int     main(void)
{
        const char      *str1 = "ls -al | wc -l";
//      const char      *str2 = "awl '{print $2}'";
//      const char      *str3 = "ps | wc -l > test.txt";


        printf("Absract Syntax Tree\n");
        print_tree(parse(tokenize(str1)), 0);

        /*
        print_list(tokenize("echo Hello World | >>"));
        printf("\n");

        print_list(tokenize("ls | grep .txt"));
        printf("\n");
        print_list(tokenize(str1));
        printf("\n");
        print_list(tokenize(str2));
        printf("\n");
        print_list(tokenize(str3));
        printf("\n");
        print_list(tokenize("echo; '{hello wolrd $3}' >> ji "));
        printf("\n");
        print_list(tokenize("    "));
        printf("\n");
        print_list(tokenize(""));
        printf("\n");
        print_list(tokenize("ls -@ /"));
        printf("\n");
        print_list(tokenize("echo Hello\\ World"));
        printf("\n");
        print_list(tokenize("echo $PATH"));
        printf("\n");
        print_list(tokenize("echo hello*world"));
        printf("\n");
        print_list(tokenize("echo $HOME"));
        printf("\n");
        print_list(tokenize("echo hello\" world"));
        printf("\n");
        */
}
