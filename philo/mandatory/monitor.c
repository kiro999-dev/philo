/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:33:31 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/29 16:11:48 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_not_finsh(pthread_mutex_t *mtx, int *isfinsh)
{
	int	val;

	pthread_mutex_lock(mtx);
	val = *isfinsh;
	pthread_mutex_unlock(mtx);
	return (val);
}

void	finish(t_data *d)
{
	pthread_mutex_lock(&d->finsh_mtx);
	d->isfinsh = 0;
	pthread_mutex_unlock (&d->finsh_mtx);
}

int	check_philo(t_philo *philo)
{
	size_t	elapsed;

	pthread_mutex_lock(&philo->data->check_mtx);
	if (philo->last_eat == 0)
		elapsed = get_current_time() - philo->data->start_time;
	else
		elapsed = get_current_time() - philo->last_eat;
	if (philo->meal_count >= philo->data->meal_num)
	{
		philo->isfull = 1;
		pthread_mutex_unlock(&philo->data->check_mtx);
		return (2);
	}
	if (elapsed > philo->data->time_die && !philo->isfull)
	{
		write_status(philo, DIE);
		finish(philo->data);
		pthread_mutex_unlock(&philo->data->check_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_mtx);
	return (0);
}

int	check_meals(t_data *d)
{
	int	i;
	int	count;

	if (d->meal_num == -1)
		return (0);
	i = 0;
	count = 0;
	while (i < d->philo_number)
	{
		if (d->philo_class[i].isfull)
			count++;
		i++;
	}
	return (count == d->philo_number);
}

void	check_sum(t_data *d)
{
	int	i;

	i = 0;
	while (get_current_time() < d->start_time)
	{
		usleep(250);
	}
	usleep(d->time_die * 1000);
	while (is_not_finsh(&d->finsh_mtx, &d->isfinsh))
	{
		i = 0;
		while (is_not_finsh(&d->finsh_mtx, &d->isfinsh) && i < d->philo_number)
		{
			if (check_philo(&d->philo_class[i]) == 1)
				break ;
			i++;
		}
		if (check_meals(d))
			finish(d);
		usleep(500);
	}
}
