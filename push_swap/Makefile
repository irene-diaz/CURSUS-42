# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME		= push_swap

# Directorios
SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= includes

# Compilación
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INCLUDE_DIR)

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parse_args.c \
		$(SRC_DIR)/stack.c \
		$(SRC_DIR)/push_swap.c \
		$(SRC_DIR)/operations.c \
		$(SRC_DIR)/oper_push.c \
		$(SRC_DIR)/oper_swap.c \
		$(SRC_DIR)/oper_rotate.c \
		$(SRC_DIR)/oper_reverse_rotate.c \
		$(SRC_DIR)/sort_small.c \
		$(SRC_DIR)/ksort.c \
		$(SRC_DIR)/assign_indexes.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_substr.c \

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) $(MAP)

.PHONY: all clean fclean re run
