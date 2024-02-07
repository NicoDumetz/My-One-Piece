##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile compile my hunter
##

SRC	=	main.c \
		animation.c \
		set_perso.c \
		my_random.c \
		action.c \
		background.c \
		change.c \
		final.c \
		my_getnbr.c \
		my_strcat.c \
		my_strlen.c \
		my_putstr.c \
		my_hunter.c


OBJ	=	$(SRC:.c=.o)

CFLAGS += -g

NAME 	= 	my_hunter

LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm *.o

fclean:		clean
	rm -f $(NAME)

re:	fclean all
