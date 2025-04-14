DIR = bonus
SRC = $(DIR)/philo_bonus.c $(DIR)/ft_atoi.c $(DIR)/philo_time_bonus.c $(DIR)/parsing_bonus.c \
	$(DIR)/philo_bonus_init.c $(DIR)/philo_monitor_bonus.c
OBJ = $(SRC:.c=.o)
NAME = philo_bonus
INC = philo_bonus.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(PTHREAD) $(CFLAGS) $(OBJ) -o $@ 

%.o : %.c $(INC)
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all