CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g
#LDFLAGS = -fsanitize=address
SRCS = main.cpp \
		Bureaucrat.cpp \
		AForm.cpp \
		ShrubberyCreationForm.cpp \
		RobotomyRequestForm.cpp \
		PresidentialPardonForm.cpp
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
NAME = AForm
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