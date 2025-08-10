NAME = libft.a

SRCS = ft_strlen.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_split.c \
	ft_free_split.c \
	# main.c \

OBJS = $(SRCS:.c=.o)

HEADERS = libft.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run 