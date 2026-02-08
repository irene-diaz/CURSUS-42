# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME		= philo

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
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/utils.c \
		

# Obtener .o desde .c 
#(“Toma cada archivo de $(SRC) que encaje con src/%.c” “Y devuélveme el mismo nombre pero en obj/%.o”)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

# Compilar cada .o en obj/
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