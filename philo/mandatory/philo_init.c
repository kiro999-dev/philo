/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:15:30 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/08 21:53:35 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(void)
{
	printf("pleas enter :\n");
	printf("[number_of_philosophers] ");
	printf("[time_to_die time] ");
	printf("[to_eat time_to_sleep] ");
	printf("[number_of_times_each_philosopher_must_eat](optional)\n");
	return (0);
}

void	philo_forks_inite2(t_data *d, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (d->philo_class[i].philo_id % 2 == 0)
		{
			d->philo_class[i].fork1 = &d->forks_arr[i];
			d->philo_class[i].fork2 = &d->forks_arr[(i + 1) % d->philo_number];
		}
		else
		{
			d->philo_class[i].fork1 = &d->forks_arr[(i + 1) % d->philo_number];
			d->philo_class[i].fork2 = &d->forks_arr[i];
		}
		i++;
	}
}

int	philo_forks_inite(t_data *d, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		d->philo_class[i].philo_id = i + 1;
		d->philo_class[i].meal_count = 0;
		d->philo_class[i].data = d;
		d->philo_class[i].isfull = 0;
		d->philo_class[i].last_eat = 0;
		d->isfinsh = 1;
		if (mutex_init(&d->forks_arr[i].fork))
			return (1);
		if (mutex_init(&d->check_mtx))
			return (1);
		if (mutex_init(&d->finsh_mtx))
			return (1);
		if (mutex_init(&d->msg))
			return (1);
		i++;
	}
	philo_forks_inite2(d, n);
	return (0);
}

int	data_init(t_data *d)
{
	int	n;

	n = d->philo_number;
	d->forks_arr = malloc(sizeof(t_forks) * n);
	if (!d->forks_arr)
		return (printf("malloc fail\n"), 1);
	d->philo_class = malloc(sizeof(t_philo) * n);
	if (!d->philo_class)
		return (free(d->forks_arr), printf("malloc fail\n"), 1);
	return (philo_forks_inite(d, n));
}
