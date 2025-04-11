/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:08:58 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/11 18:38:39 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define DIE 4
# define THINKS 5

struct	s_data ;
struct	s_philo_bonus;

typedef struct s_data
{
	struct s_philo_bonus	*philo_class;
	int						philo_number;
	size_t					time_die;
	int						time_to_sleep;
	int						time_to_eat;
	int						meal_num;
	size_t					start_time;
	int						isfinish;
	sem_t					*forks;
	sem_t					*message;
	sem_t					*finish;
	sem_t					*check;
	short int				all_full;
}	t_data;

typedef struct s_philo_bonus
{
	struct s_data	*data;
	pid_t			pid;
	size_t			last_eat;
	int				philo_id;
	int				meal_count;
	short int		isfull;
}	t_philo_bonus;

long long	ft_atoi(const char *str, int *flagerr);
int			parsing(int argc, char **argv, t_data *d);
void		write_status(t_philo_bonus *p, int status);
int			init_data(t_data *d);
size_t		get_current_time(void);
void		ft_usleep(size_t time);
void		*check_philos(void *data);
void		ft_destroy_all(t_data *d, t_philo_bonus *philo);

#endif