/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/15 13:59:17 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	d->start_time = get_current_time();
	printf("%ld 1 has taken a fork\n", d->start_time - get_current_time());
	ft_usleep(d->time_die, d);
	printf ("%ld 1 died\n", get_current_time() - d->start_time);
	return (NULL);
}

void	start(t_data *d)
{
	pthread_t	p1;

	if (d->philo_number == 1)
	{
		if (pthread_create(&p1, NULL, one_philo, d) != 0)
			return ;
		if (pthread_join(p1, NULL) != 0)
			return ;
		return ;
	}
	creat_philos(d);
}

int	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philo_number)
	{
		pthread_mutex_destroy(&d->forks_arr[i].fork);
		i++;
	}
	free(d->forks_arr);
	free(d->philo_class);
	pthread_mutex_destroy(&d->check_mtx);
	pthread_mutex_destroy(&d->philo_mtx);
	pthread_mutex_destroy(&d->finsh_mtx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		flagerr;

	if (argc == 5)
	{
		if (fill_data(&data, argv, -1, 0))
			return (1);
	}
	else if (argc == 6)
	{
		if (fill_data(&data, argv, ft_atoi(argv[5], &flagerr), 1))
			return (1);
	}
	else
		return (print_msg(), 1);
	if (data_init(&data))
		return (free_data(&data));
	start(&data);
	free_data(&data);
	return (0);
}
