DIR = mandatory
SRC = $(DIR)/philo.c $(DIR)/ft_atoi.c $(DIR)/philo_init.c $(DIR)/init_mutex.c $(DIR)/status.c \
	$(DIR)/write_status.c $(DIR)/philo_time.c $(DIR)/monitor.c $(DIR)/parsing_philo.c
OBJ = $(SRC:.c=.o)
NAME = philo

CC = cc 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(PTHREAD) $(CFLAGS) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ:.o=.d)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

-include $(OBJ:.o=.d)
