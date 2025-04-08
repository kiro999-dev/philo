/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:02:55 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/08 12:43:38 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *p, int status)
{
	size_t		elapsed;

	pthread_mutex_lock(&p->data->philo_mtx);
	elapsed = get_current_time() - p->data->start_time;
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
	pthread_mutex_unlock(&p->data->philo_mtx);
}
