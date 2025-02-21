/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:25:24 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/21 14:50:10 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(pthread_mutex_t *m1, pthread_mutex_t *m2, pthread_mutex_t *m3)
{
	pthread_mutex_unlock(m1);
	pthread_mutex_unlock(m2);
	pthread_mutex_unlock(m3);
}

void	eating(t_philo *p)
{
	pthread_mutex_lock(&p->fork1->fork);
	if (!is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
	{
		pthread_mutex_unlock(&p->fork1->fork);
		return ;
	}
	write_status(p, TAKE_FORK);
	pthread_mutex_lock(&p->fork2->fork);
	write_status(p, TAKE_FORK);
	write_status(p, EAT);
	pthread_mutex_lock(&p->data->check_mtx);
	p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->data->check_mtx);
	ft_usleep(p->data->time_to_eat, p->data);
	pthread_mutex_lock(&p->data->check_mtx);
	if (!p->isfull)
		p->meal_count++;
	unlock(&p->fork1->fork, &p->fork2->fork, &p->data->check_mtx);
}

void	sleeping(t_philo *p)
{
	write_status(p, SLEEP);
	ft_usleep(p->data->time_to_sleep, p->data);
}

void	*dinner(void *d)
{
	t_philo	*p;

	p = (t_philo *) d;
	while (is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
	{
		pthread_mutex_lock(&p->data->check_mtx);
		if (p->isfull)
		{
			pthread_mutex_unlock(&p->data->check_mtx);
			break ;
		}
		pthread_mutex_unlock(&p->data->check_mtx);
		eating(p);
		sleeping(p);
		write_status(p, THINKS);
	}
	return (NULL);
}

void	creat_philos(t_data *d)
{
	int	i;

	i = 0;
	d->start_time = get_current_time();
	while (i < d->philo_number)
	{
		if (pthread_create(&d->philo_class[i].philos_t,
				NULL, dinner, &d->philo_class[i]) != 0)
			return ;
		i++;
	}
	check_sum(d);
	i = 0;
	while (i < d->philo_number)
	{
		if (pthread_join(d->philo_class[i].philos_t, NULL) != 0)
			return ;
		i++;
	}
}
