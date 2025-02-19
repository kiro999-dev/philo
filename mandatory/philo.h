/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:46 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/19 17:20:40 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h> 
# include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define take_fork 1
#define eat 2
#define sleep 3
#define die 4
#define thinks 5
struct s_data ;
struct s_philo;
typedef struct s_forks
{
	int fork_id;
	pthread_mutex_t fork;
}t_forks;

typedef struct s_data
{
	struct s_philo 	*philo_class;
	int			philo_number;
	size_t			time_die;
	int			time_to_sleep;
	int			time_to_eat;
	int			meal_num;
	size_t		start_time;
	int			isfinsh;
	t_forks 	*forks_arr;
	pthread_mutex_t philo_mtx;
	pthread_mutex_t finsh_mtx;
	pthread_mutex_t check_mtx;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philos_t;
	size_t 			last_eat;
	int 			philo_id;
	int				philo_vist;
	int 			meal_count;
	t_forks			*fork1;
	t_forks			*fork2;
	short int		isfull;
	int				checked;
}	t_philo;


int	ft_atoi(const char *str);
int	print_msg();
int mutex_init(pthread_mutex_t *mtx);
int	data_init(t_data *d);
size_t	get_current_time(void);
int is_not_finsh(pthread_mutex_t *mtx,int *isfinsh);
void ft_usleep(size_t time,t_data *d);
void creat_philos(t_data *d);
void write_status(t_philo *p, int status);
void check_sum(t_data *d);
void finish(t_data *d);
#endif