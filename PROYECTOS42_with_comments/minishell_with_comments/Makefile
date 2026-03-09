NAME = minishell
CC = cc
CFLAGS = -g 
#RECORDAR METER WALL WEXTRA WERROR
#CFLAGS = -fsanitize=address -g
LDFLAGS = -lreadline
#LDFLAGS = -fsanitize=address -lreadline

INC_DIR = includes
LIBFT_DIR = libft
LIBFT_ARENA_DIR = libft_arena

SRCS = main.c \
       reader/reader.c \
       tokenizer/tokenizer.c \
       parser/check_syntax.c \
       parser/parser.c \
       parser/parser_utils.c \
       memory/arena_destroy.c \
       memory/arena_init.c \
	   executor/execute.c \
	   executor/execute_chain.c \
	   executor/execute_redirections.c \
	   executor/execute_utils.c \
	   executor/builtins.c \
	   executor/builtins/cd.c \
       executor/builtins/exit.c \
       executor/builtins/pwd.c \
       executor/builtins/echo.c \
       executor/builtins/export.c \
       executor/builtins/unset.c \
	   executor/signals.c \

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_ARENA = $(LIBFT_ARENA_DIR)/libft_arena.a

all: check_readline $(LIBFT) $(LIBFT_ARENA) $(NAME)

check_readline:
	@if ! echo "#include <readline/readline.h>" | $(CC) -E - >/dev/null 2>&1; then \
		echo "Error: libreadline is not installed"; \
		echo "Run: sudo apt-get install libreadline-dev"; \
		exit 1; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_ARENA_DIR) -c $< -o $@
#	$(CC) $(LDFLAGS) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBFT_ARENA_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBFT_ARENA):
	make -C $(LIBFT_ARENA_DIR)

$(NAME): $(OBJS) $(LIBFT) $(LIBFT_ARENA)
	$(CC) $(OBJS) $(LIBFT_ARENA) $(LIBFT) $(LDFLAGS) -o $(NAME)


clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBFT_ARENA_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBFT_ARENA_DIR)

re: fclean all

.PHONY: all clean fclean re check_readlin
