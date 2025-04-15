/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:20:54 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/15 14:01:21 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_philos(void *data)
{
	t_philo_bonus	*p;
	size_t			elapsed;

	elapsed = 0;
	p = (t_philo_bonus *)data;
	while (1)
	{
		sem_wait(p->data->check);
		elapsed = get_current_time() - p->last_eat;
		if ((elapsed > p->data->time_die && p->last_eat != 0))
		{
			write_status(p, DIE);
			sem_post(p->data->check);
			sem_post(p->data->finish);
		}
		sem_post(p->data->check);
		sem_wait(p->data->meals);
		if (p->meal_count >= p->data->meal_num + 1 && p->data->meal_num != -1)
			sem_post(p->data->finish);
		sem_post(p->data->meals);
		usleep(100);
	}
	return (NULL);
}
