NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lreadline
INC_DIR = includes
LIBFT_DIR = libft
LIBFT_ARENA_DIR = libft_arena
OBJ_DIR = obj
SRCS := main.c \
	main_utils.c \
	reader/reader.c \
	reader/reader_utils.c \
	tokenizer/tokenizer.c \
	tokenizer/tokenizer_utils.c \
	parser/check_syntax.c \
	parser/check_syntax_args.c \
	parser/check_syntax_main.c \
	parser/parser.c \
	parser/parser_init.c \
	parser/parser_utils.c \
	parser/parser_heredoc_utils.c \
	parser/parser_heredoc_pasted.c \
	parser/parser_heredoc_main.c \
	memory/arena_destroy.c \
	memory/arena_init.c \
	executor/execute.c \
	executor/execute_chain.c \
	executor/execute_redirections.c \
	executor/execute_utils.c \
	executor/execute_utils2.c \
	executor/builtins.c \
	executor/builtins/cd.c \
	executor/builtins/exit.c \
	executor/builtins/pwd.c \
	executor/builtins/echo.c \
	executor/builtins/env_utils.c \
	executor/builtins/export.c \
	executor/builtins/unset.c \
	executor/signals.c \
	expander/expander.c \
	expander/expander_heredoc.c \
	expander/expand_var.c \
	expander/expander_utils.c \
	expander/expander_wildcard.c
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_ARENA = $(LIBFT_ARENA_DIR)/libft_arena.a
all: check_readline $(LIBFT) $(LIBFT_ARENA) $(NAME)
check_readline:
	@if ! echo "#include <readline/readline.h>" | $(CC) -E - >/dev/null 2>&1; then \
		echo "Error: libreadline is not installed"; \
		echo "Run: sudo apt-get install libreadline-dev"; \
		exit 1; \
	fi
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_ARENA_DIR) -c $< -o $@
$(LIBFT):
	make -C $(LIBFT_DIR)
$(LIBFT_ARENA):
	make -C $(LIBFT_ARENA_DIR)
$(NAME): $(OBJS) $(LIBFT) $(LIBFT_ARENA)
	$(CC) $(OBJS) $(LIBFT_ARENA) $(LIBFT) $(LDFLAGS) -o $(NAME)
minishell_asan: check_readline $(LIBFT) $(LIBFT_ARENA)
	$(CC) -fsanitize=address $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_ARENA_DIR) $(SRCS) $(LIBFT_ARENA) $(LIBFT) $(LDFLAGS) -o minishell_asan
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBFT_ARENA_DIR)
fclean: clean
	rm -f $(NAME)
	rm -f minishell_asan
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBFT_ARENA_DIR)
re: fclean all
bonus: all
	@echo "Bonus rule executed!"
	$(MAKE) all
.PHONY: all clean fclean re check_readline minishell_asan bonus
