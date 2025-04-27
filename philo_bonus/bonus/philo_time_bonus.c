/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:09:12 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/27 14:59:52 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_semaphores(t_data *d)
{
	if (!d->check || !d->finish
		|| !d->forks || !d->meals || !d->message)
	{
		printf("sem_open fail\n");
		sem_close(d->check);
		sem_close(d->message);
		sem_close(d->finish);
		sem_close(d->forks);
		sem_close(d->meals);
		free(d->philo_class);
		exit(1);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, " Erorr :gettimeofday() error\n", 30);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		usleep(500);
	}
}
