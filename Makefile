DIR = mandatory
SRC = $(DIR)/philo.c $(DIR)/ft_atoi.c $(DIR)/error_msg.c $(DIR)/philo_init.c $(DIR)/init_mutex.c
OBJ = $(SRC:.c=.o)
NAME = philo
INC = philo.h
CC = cc 
CFLAGS = -Wall -Wextra -Werror 
PTHREAD = -pthread
all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(PTHREAD) $(CFLAGS) $(OBJ) -o $@

%.o : %.c $(INC)
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm $(OBJ)

fclean : clean
	rm $(NAME)
	
re : fclean all