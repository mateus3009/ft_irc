NAME := ircserv

DIRECTORY_SOURCE	:= ./src
DIRECTORY_HEADER	:= ./include
DIRECTORY_TARGET	:= target

FILE_SOURCE		:= $(filter %.cpp, $(shell find $(DIRECTORY_SOURCE) -type f))

OBJECTS_SOURCE	:= $(addprefix $(DIRECTORY_TARGET)/, $(FILE_SOURCE:.cpp=.o))

COMPILER		:= clang++
COMPILER_FLAGS	:= -Wall -Wextra -Werror -g --std=c++98

.PHONY : all clean fclean make re bonus
.SILENT : all clean fclean make re bonus

all : $(NAME)

clean :
	@rm -rf $(DIRECTORY_TARGET)

fclean :
	@rm -f $(NAME)
	@rm -rf $(DIRECTORY_TARGET)

re : clean all

$(NAME) : $(OBJECTS_SOURCE)
	@$(COMPILER) $(COMPILER_FLAGS) $(OBJECTS_SOURCE) -o $(NAME)

$(DIRECTORY_TARGET)/%.o : %.cpp
	@mkdir -p $(@D)
	@$(COMPILER) -I$(DIRECTORY_HEADER) $(COMPILER_FLAGS) -c $< -o $@
