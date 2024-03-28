CC = cc

CFLAGS = 

INCLUDES = -I./libft

RDLINE = -lreadline

NAME = minishell

CFILES = lexer.c \
	 parser.c \
	 linked_lists.c \
	 trees.c \
	 minishell.c \
	 executor.c \
	 utils.c \
	 utils2.c \
	 executor_redir_out.c \
	 executor_redir_append.c \

OBJECTS = $(CFILES:.c=.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(RDLINE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
