/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:46 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 10:02:58 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <time.h> 
# include <pthread.h>

typedef struct s_data;

typedef struct s_philo
{
	t_data		*data;
	pthread_t	*philos_arr;
	int			meal_eat;
	int 		last_eat;
	int 		philo_id;
}	t_philo;
typedef struct s_data
{
	int	philo_number;
	int	time_die;
	int	time_to_sleep;
	int	meal_num;
	t_philo *philo_class;
}	t_data;


int	ft_atoi(const char *str);
int	print_msg();
#endif