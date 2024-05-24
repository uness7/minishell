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

all: $(NAME)

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
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/utils_%.o: $(UTILS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/execution_%.o: $(EXECUTION)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/builtins_%.o: $(BUILTINS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/expander_%.o: $(EXPANDER)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/lexer_%.o: $(LEXER)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/parser_%.o: $(PARSER)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/signals_%.o: $(SIGNALS)/%.c
	@mkdir -p $(dir $@)
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

.PHONY: all run help clean fclean re
