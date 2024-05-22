# Directories
INCLUDE = include
BUILD = build
SRC = src
UTILS = $(SRC)/utils
EXECUTION = $(SRC)/execution
BUILTINS = $(SRC)/builtins
EXPANDER = $(SRC)/expander
LEXER = $(SRC)/lexer
PARSER = $(SRC)/parser
SIGNALS = $(SRC)/signals

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE)
RDLINE = -lreadline

# Target executable
NAME = minishell

# Main source file
MAIN = minishell.c

# Source files
CFILES = $(MAIN) \
	 $(wildcard $(SRC)/*.c) \
	 $(wildcard $(UTILS)/*.c) \
	 $(wildcard $(EXECUTION)/*.c) \
	 $(wildcard $(BUILTINS)/*.c) \
	 $(wildcard $(EXPANDER)/*.c) \
	 $(wildcard $(LEXER)/*.c) \
	 $(wildcard $(PARSER)/*.c) \
	 $(wildcard $(SIGNALS)/*.c)

# Object files
OBJECTS = $(patsubst %.c, $(BUILD)/%.o, $(MAIN))
OBJECTS += $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(wildcard $(SRC)/*.c))
OBJECTS += $(patsubst $(UTILS)/%.c, $(BUILD)/utils_%.o, $(wildcard $(UTILS)/*.c))
OBJECTS += $(patsubst $(EXECUTION)/%.c, $(BUILD)/execution_%.o, $(wildcard $(EXECUTION)/*.c))
OBJECTS += $(patsubst $(BUILTINS)/%.c, $(BUILD)/builtins_%.o, $(wildcard $(BUILTINS)/*.c))
OBJECTS += $(patsubst $(EXPANDER)/%.c, $(BUILD)/expander_%.o, $(wildcard $(EXPANDER)/*.c))
OBJECTS += $(patsubst $(LEXER)/%.c, $(BUILD)/lexer_%.o, $(wildcard $(LEXER)/*.c))
OBJECTS += $(patsubst $(PARSER)/%.c, $(BUILD)/parser_%.o, $(wildcard $(PARSER)/*.c))
OBJECTS += $(patsubst $(SIGNALS)/%.c, $(BUILD)/signals_%.o, $(wildcard $(SIGNALS)/*.c))


banner:
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

# Rules
all: banner $(NAME)

run: $(NAME)
	@echo "🏃 Running Minishell..."
	@sleep 1
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

$(BUILD)/%.o: %.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/utils_%.o: $(UTILS)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/execution_%.o: $(EXECUTION)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/builtins_%.o: $(BUILTINS)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/expander_%.o: $(EXPANDER)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/lexer_%.o: $(LEXER)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/parser_%.o: $(PARSER)/%.c
	@mkdir -p $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/signals_%.o: $(SIGNALS)/%.c
	@mkdir -p $(BUILD)
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

.PHONY: all banner run help clean fclean re
