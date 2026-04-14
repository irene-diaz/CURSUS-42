CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
LDFLAGS = -fsanitize=address
SRCS = main.cpp \
	   Weapon.cpp \
	   HumanA.cpp \
	   HumanB.cpp
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
NAME = weapon

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all