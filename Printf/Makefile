NAME = libftprintf.a

EXE = ./main

SRCS = ft_printf.c \
	format_string.c \
	utils.c\
	main.c \

OBJS = $(SRCS:.c=.o)

#BONUS_FILES = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \

#BONUS_OBJS = $(BONUS_FILES:.c=.o)

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

run: $(NAME)
	cc -o $(EXE) $(OBJS) -L. -l:$(NAME)

.PHONY: all clean fclean re run