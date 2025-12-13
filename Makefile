NAME = result

CC = cc

CCFLAG = -Wall -Wextra -Werror -D BUFFER_SIZE=1024

SRC = get_next_line_utils.c   get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
%.o:%.c Makefile get_next_line.h
	@printf "\033[1;92mCompiled 👌🏽%s\033[0m\n" $@
	@$(CC) $(CCFLAG) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)
re: fclean all 

.PHONY: clean fclean all re