NAME := ircserv

DIRECTORY_SOURCE	:= ./srcs
DIRECTORY_HEADER	:= ./includes
DIRECTORY_TARGET	:= target

FILE_SOURCE		:= $(filter %.cpp, $(shell find $(DIRECTORY_SOURCE) -type f))

OBJECTS_SOURCE	:= $(addprefix $(DIRECTORY_TARGET)/, $(FILE_SOURCE:.cpp=.o))

COMPILER		:= c++
COMPILER_FLAGS	:= -Wall -Wextra -Werror --std=c++98

.PHONY : all clean fclean make re test
.SILENT : all clean fclean make re test

all : $(NAME)

clean :
	@rm -rf $(DIRECTORY_TARGET)

fclean :
	@rm -f $(NAME)
	@rm -rf $(DIRECTORY_TARGET)

re : clean all

test : $(NAME)
	valgrind --leak-check=full --track-origins=yes -q ./$(NAME) 8081 42

$(NAME) : $(OBJECTS_SOURCE)
	@$(COMPILER) $(COMPILER_FLAGS) $(OBJECTS_SOURCE) -o $(NAME)

$(DIRECTORY_TARGET)/%.o : %.cpp
	@mkdir -p $(@D)
	@$(COMPILER) -I$(DIRECTORY_HEADER) $(COMPILER_FLAGS) -c $< -o $@
