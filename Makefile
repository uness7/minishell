CC = cc

CFLAGS = -Wall -Wextra -Werror

RDLINE = -lreadline

NAME = minishell

CFILES = lexer.c \
	 parser.c \
	 linked_lists.c \
	 trees.c \
	 minishell.c \

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(RDLINE)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
