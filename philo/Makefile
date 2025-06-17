CC= cc
CFLAGS= -Wall -Wextra -Werror
name= philo
SRC= init.c	main.c	message.c	parsing.c\
philosopher.c	philo_status.c	simulation.c	utilis.c
OBJ= $(SRC:.c=.o)

all: $(name)

$(name): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(name)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean re