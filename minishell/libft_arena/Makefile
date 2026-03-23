NAME = libft_arena.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_strcpy.c \
       ft_strncpy.c \
       ft_strjoin_arena.c \
       ft_split_arena.c \
       ft_strdup_arena.c \
       ft_substr_arena.c \
       ft_strtrim_arena.c \
       ft_itoa_arena.c \
       ft_strmapi_arena.c \
       ft_calloc_arena.c \
       ft_lstnew_arena.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
