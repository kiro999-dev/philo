/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:08:38 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/27 15:08:11 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clean_all(t_data *d, t_philo_bonus *philo)
{
	int	i;

	i = 0;
	while (i < d->philo_number)
		kill(philo[i++].pid, SIGKILL);
	sem_close(d->check);
	sem_close(d->message);
	sem_close(d->finish);
	sem_close(d->forks);
	sem_close(d->meals);
	free(philo);
}

void	write_status(t_philo_bonus *p, int status)
{
	size_t	elapsed;

	sem_wait(p->data->message);
	elapsed = get_current_time() - p->data->start_time;
	if (status == EAT)
		printf("%ld %d is eating\n", elapsed, p->philo_id);
	if (status == DIE)
		printf("%ld %d died\n", elapsed, p->philo_id);
	if (status == TAKE_FORK)
		printf("%ld %d has taken a fork\n", elapsed, p->philo_id);
	if (status == SLEEP)
		printf("%ld %d is sleeping\n", elapsed, p->philo_id);
	if (status == THINKS)
		printf("%ld %d is thinking\n", elapsed, p->philo_id);
	if (status != DIE)
		sem_post(p->data->message);
}

void	ft_create_semaphores(t_data *d)
{
	sem_unlink("/death");
	sem_unlink("/check");
	sem_unlink("/meals");
	sem_unlink("/message");
	sem_unlink("/forks");
	d->finish = sem_open("/death", O_CREAT, 0600, 1);
	d->check = sem_open("/check", O_CREAT, 0600, 1);
	d->meals = sem_open("/meals", O_CREAT, 0600, 1);
	d->message = sem_open("/message", O_CREAT, 0600, 1);
	d->forks = sem_open("/forks", O_CREAT, 0600,
			d->philo_number);
	check_semaphores(d);
}

void	init_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philo_number)
	{
		d->philo_class[i].data = d;
		d->philo_class[i].philo_id = i + 1;
		d->philo_class[i].meal_count = 0;
		d->philo_class[i].last_eat = 0;
		d->philo_class[i].pid = -1;
		d->start_time = 0;
		d->philo_class[i].isfull = 0;
		i++;
	}
}

int	init_data(t_data *d)
{
	d->philo_class = malloc(sizeof(t_philo_bonus) * d->philo_number);
	if (d->philo_class == NULL)
		return (1);
	init_philo(d);
	ft_create_semaphores(d);
	return (0);
}
