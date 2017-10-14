NAME = fillit

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

HDDIRS = fillit.h

SRC = board.c board2.c main.c solve.c tetro.c tetro2.c verify.c verify2.c

OBJ = $(SRC:.c=.o)

$(NAME) : fillit.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ) *.gch

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
