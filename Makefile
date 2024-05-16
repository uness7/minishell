CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RDLINE = -lreadline

NAME = minishell

CFILES = lexer.c \
	 lexer2.c \
	 parser.c \
	 parser2.c \
	 parser3.c \
	 linked_lists.c \
	 trees.c \
	 minishell.c \
	 utils.c \
	 utils2.c \
	 utils3.c \
	 utils4.c \
	 utils5.c \
	 utils6.c \
	 utils7.c \
	 ft_exit.c \
	 ft_pwd.c \
	 ft_cd.c \
	 ft_envi.c \
	 ft_envi2.c \
	 ft_export.c \
	 ft_echo.c \
	 ft_echo2.c \
	 ft_echo3.c \
	 builtins.c \
	 builtins2.c \
	 builtins3.c \
	 signal.c \
	 errors.c \
	 errors2.c \
	 itoa.c \
	 dodjo.c \
	 expander.c \
	 split_echo.c \
	 execute.c \
	 isTreeValid.c \

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

banner :
	@echo "\n"
	@echo "⏳ Files are being compiled. ⏳  \n"
	@echo "888      .d88888b.        d8888 8888888b. 8888888 888b    888  .d8888b."
	@echo "888     d88P   Y88b      d88888 888   Y88b  888   8888b   888 d88P  Y88b"
	@echo "888     888     888     d88P888 888    888  888   88888b  888 888    888"
	@echo "888     888     888    d88P 888 888    888  888   888Y88b 888 888"
	@echo "888     888     888   d88P  888 888    888  888   888 Y88b888 888  88888"
	@echo "888     888     888  d88P   888 888    888  888   888  Y88888 888    888"
	@echo "888     Y88b. .d88P d8888888888 888  .d88P  888   888   Y8888 Y88b  d88P"
	@echo "88888888  Y88888P  d88P     888 8888888P  8888888 888    Y888  Y8888P88"
	@echo "\n"
	@sleep 1

run: $(NAME)
	@echo "🏃 Running Minishell..."
	#@sleep 1
	@clear
	@./$(NAME)

help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all      : Build the minishell"
	@echo "  clean    : Remove object files"
	@echo "  fclean   : Remove object files and executable"
	@echo "  re       : Rebuild the minishell"
	@echo "  run      : Run the minishell"
	@echo "  help     : Show this help message"

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(RDLINE)
	@echo "✅  Operation Is Finished. ✅ \n"
	@echo "🆘  For Help On How To Run This Program Run : make help. 🆘  \n"
	@echo "🥷  Enjoy NinjaShell  🥷 \n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "\n"
	@rm -f $(OBJECTS)
	@echo "🧼 Directory Is Cleaned. 🧼 \n"

fclean: clean
	@rm -f $(NAME)
	@echo "🧼 Executable Is Cleaned As Well. 🧼 \n"
	@echo "\n"

re: fclean all
