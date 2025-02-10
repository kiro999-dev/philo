/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:15:30 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 18:10:18 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_forks_inite2(t_data *d,int n)
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
			d->philo_class[i].fork2 = &d->forks_arr[i];
			d->philo_class[i].fork1 = &d->forks_arr[(i + 1) % d->philo_number];
		}
		i++;
	}
}

int philo_forks_inite(t_data *d,int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		d->philo_class[i].philo_id = i + 1;
		d->philo_class[i].meal_count = 0;
		d->forks_arr[i].fork_id = i + 1;
		d->philo_class[i].data = d;
		d->philo_class[i].philo_vist = 0;
		d->isready = 0;
		d->isfull = 0;
		if(mutex_init(&d->forks_arr[i].fork))
			return (1);
		if(mutex_init(&d->philo_mtx))
			return (1);
		i++;
	}
	philo_forks_inite2(d,n);
	return(0);
}

int	data_init(t_data *d)
{
	int	n;
	
	n = d->philo_number;
	d->start_time = get_current_time();
	d->forks_arr = malloc(sizeof(t_forks) * n);
	if(!d->forks_arr)
		return (printf("malloc fail\n"), 1);
	d->philo_class = malloc(sizeof(t_philo) * n);
	if (!d->philo_class)
		return (free(d->forks_arr), printf("malloc fail\n"), 1);
	return (philo_forks_inite(d,n));
}