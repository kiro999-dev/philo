/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:46 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 17:06:50 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <time.h> 
# include <pthread.h>
#include <stdlib.h>

struct s_data;
typedef struct s_forks
{
	int fork_id;
	pthread_mutex_t fork;
}t_forks;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philos_t;
	int 			last_eat;
	int 			philo_id;
	int 			meal_count;
	t_forks			*fork1;
	t_forks			*fork2;
	pthread_mutex_t philo_mtx;

}	t_philo;
typedef struct s_data
{
	int			philo_number;
	int			time_die;
	int			time_to_sleep;
	int			meal_num;
	short int	isfull;
	int			isready;
	t_philo 	*philo_class;
	t_forks 	*forks_arr;
}	t_data;


int	ft_atoi(const char *str);
int	print_msg();
int mutex_init(pthread_mutex_t *mtx);
int	data_init(t_data *d);
#endif