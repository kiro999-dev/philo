/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:02:55 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/08 20:53:30 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *p)
{
	write_status(p, THINKS);
	if (p->data->philo_number % 2 != 0)
	{
		if (p->data->time_to_sleep < p->data->time_to_eat)
			ft_usleep(p->data->time_to_eat - p->data->time_to_sleep, p->data);
		usleep(1000);
	}
}

void	write_status(t_philo *p, int status)
{
	size_t		elapsed;
	size_t		time_start;

	time_start = p->data->start_time;
	pthread_mutex_lock(&p->data->msg);
	elapsed = get_current_time() - time_start;
	if (status == EAT && is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
		printf("%ld %d is eating\n", elapsed, p->philo_id);
	if (status == DIE && is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
		printf("%ld %d died\n", elapsed, p->philo_id);
	if (status == TAKE_FORK
		&& is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
		printf("%ld %d has taken a fork\n", elapsed, p->philo_id);
	if (status == SLEEP && is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
		printf("%ld %d is sleeping\n", elapsed, p->philo_id);
	if (status == THINKS
		&& is_not_finsh(&p->data->finsh_mtx, &p->data->isfinsh))
		printf("%ld %d is thinking\n", elapsed, p->philo_id);
	pthread_mutex_unlock(&p->data->msg);
}
