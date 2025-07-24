# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME		= so_long

# Directorios
SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= includes

# Bibliotecas
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

PRINTF_DIR	= ft_printf
PRINTF_A	= $(PRINTF_DIR)/ft_printf.a

MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Compilación
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR)

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map.c \
		$(SRC_DIR)/map_utils.c \
		$(SRC_DIR)/validate.c \
		$(SRC_DIR)/validate2.c \
		$(SRC_DIR)/init_game.c \
		$(SRC_DIR)/setup_window.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/game.c \
		$(SRC_DIR)/move.c

# Obtener .o desde .c 
#(“Toma cada archivo de $(SRC) que encaje con src/%.c” “Y devuélveme el mismo nombre pero en obj/%.o”)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_A) $(PRINTF_A) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT_A) $(PRINTF_A) $(MLX_FLAGS) -o $(NAME)

# Compilar cada .o en obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build las libs externas
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF_A):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) $(MAP)

.PHONY: all clean fclean re run