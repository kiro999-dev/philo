/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonuc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:20:54 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/11 18:37:38 by zkhourba         ###   ########.fr       */
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
		if (elapsed > p->data->time_die && p->last_eat != 0)
		{
			(write_status(p, DIE), sem_post(p->data->finish));
			break ;
		}
		(sem_post(p->data->check), sem_wait(p->data->check));
		if (p->data->all_full >= p->data->meal_num && p->data->meal_num != -1)
		{
			sem_post(p->data->finish);
			break ;
		}
		sem_post(p->data->check);
	}
	return (NULL);
}
