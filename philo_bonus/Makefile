DIR = bonus
SRC = $(DIR)/philo_bonus.c $(DIR)/ft_atoi_bonus.c $(DIR)/philo_time_bonus.c $(DIR)/parsing_bonus.c \
	$(DIR)/philo_bonus_init.c $(DIR)/philo_monitor_bonus.c
OBJ = $(SRC:.c=.o)
NAME = philo_bonus
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