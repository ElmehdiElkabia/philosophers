CC= cc
# CFLAGS= -Wall -Wextra -pedantic -std=c11 
# CFLAGS= -Wall -Wextra -Werror -fsanitize=thread -g -pthread
CFLAGS= -Wall -Wextra -Werror
name= philo
SRC= main.c init.c simulation.c utilis.c
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