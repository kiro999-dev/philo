/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:20:54 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/15 14:30:47 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_data *d)
{
	d->philo_class[0].pid = fork();
	if (d->philo_class[0].pid == -1)
	{
		printf("fork fail\n");
		return ;
	}
	else if (d->philo_class[0].pid == 0)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(d->time_die);
		printf("%ld 1 died\n", d->time_die);
		exit(0);
	}
	else
		waitpid(d->philo_class[0].pid, NULL, 0);
}

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
