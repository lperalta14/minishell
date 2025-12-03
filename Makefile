# Program name
NAME = minishell

# Directories
INCLUDES_DIR = include
OBJ_DIR = obj

# Includes 
INCLUDES = $(INCLUDES_DIR)/minishell.h \
	$(INCLUDES_DIR)/libft.h \
	$(INCLUDES_DIR)/builtins.h \
	$(INCLUDES_DIR)/executor.h \
	$(INCLUDES_DIR)/expander.h \
	$(INCLUDES_DIR)/parser.h \
	$(INCLUDES_DIR)/lexer.h \
	$(INCLUDES_DIR)/utils.h

# Source directories
BUIL_DIR = src/builtins
EXE_DIR = src/executor
EXP_DIR = src/expander
PARS_DIR = src/parser
TOK_DIR = src/tokenizer
UTILS_DIR = src/utils

# Source files
BUILTINS = $(BUIL_DIR)/cdcommand.c

EXECUTOR = $(EXE_DIR)/pipes.c

EXPANDER = $(EXP_DIR)/expand.c

PARSER = $(PARS_DIR)/parse.c $(PARS_DIR)/parse_free.c $(PARS_DIR)/parse_utils.c

TOKENIZER = $(TOK_DIR)/token.c $(TOK_DIR)/quotes.c $(TOK_DIR)/utils_tokens.c

UTILS = $(UTILS_DIR)/prints/banner.c $(UTILS_DIR)/prints/tokens.c $(UTILS_DIR)/prints/parser.c

SRCS = src/main.c $(BUILTINS) $(EXECUTOR) $(EXPANDER) $(PARSER) \
	$(TOKENIZER) $(UTILS)

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT_DIR = src/my_lib
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)/includes

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDES_DIR) $(LIBFT_INC)
LDFLAGS = -lreadline

# Utils
RM = rm -rf

# Colors
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[1;33m
BLUE   = \033[0;34m
PINK   = \033[0;35m
NC     = \033[0m

# Rules
all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(PINK)🔗 Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) ready!$(NC)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(PINK)⌛ $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@echo "$(YELLOW)📚 Building libft...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ libft ready!$(NC)"

clean:
	@echo "$(RED)🗑️  Cleaning objects...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)🗑️  Full clean...$(NC)"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(BLUE)🧽 All clean!$(NC)"

re: fclean all

.PHONY: all clean fclean re