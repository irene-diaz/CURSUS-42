# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME		= philo

SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= includes

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I$(INCLUDE_DIR)

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/utils.c

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

.PHONY: all clean fclean re
