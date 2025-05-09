NAME = libftprintf.a
#EXE = ./main

SRCS = ft_printf.c \
	utils.c\
	utils2.c \
	#main.c\

OBJS = $(SRCS:.c=.o)


HEADERS = ft_printf.h

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

#bonus: $(NAME) $(BONUS_OBJS)$(AR) $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#run: $(NAME) aqui hay un enterr cc -o $(EXE) $(OBJS) -L. -l:$(NAME)

.PHONY: all clean fclean re run