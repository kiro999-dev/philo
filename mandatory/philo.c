/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 17:04:36 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int wait_philos(t_philo *philos)
{
	static int n = 0;
	pthread_mutex_lock(&philos->philo_mtx);
	n++;
	// if(n == philos->data->philo_number)
	// 	return(0);
	printf("philo %d lock\n",philos->philo_id);
	pthread_mutex_unlock(&philos->philo_mtx);
	printf("philo %d unlock\n",philos->philo_id);
	return(1);
}
void* dinner(void *data)
{
	t_data *d;

	d = (t_data *) data;
	int i = 0;
	printf("%d\n",d->philo_number);
 	while (i < d->philo_number)
	{
		wait_philos(&d->philo_class[i]);
		i++;
	}
	
	// 
	// 
	// eating();
	// sleeping();
	// thinking();
	return(NULL);
}
void	fill_data(t_data *d, char **argv, int meal)
{
	d->philo_number = ft_atoi(argv[1]);
	d->time_die = ft_atoi(argv[2]);
	d->time_to_sleep = ft_atoi(argv[3]);
	d->meal_num = meal;
}

void creat_philos(t_data *d)
{
	int i;

	i = 0;
	
	while (i < d->philo_number)
	{
		if(pthread_create(&d->philo_class[i].philos_t,NULL, dinner, d) != 0)
			return;
		i++;
	}
	i = 0;
	while (i < d->philo_number)
	{
		if(pthread_join(d->philo_class[i].philos_t,NULL) != 0)
			return;
		i++;
	}
	
}
void	start(t_data *d)
{
	creat_philos(d);
}
int  main(int argc, char **argv)
{
	t_data	data;

	if (argc == 4)
		fill_data(&data, argv, -1);
	else if (argc == 5)
		fill_data(&data, argv, ft_atoi(argv[4]));
	else
		print_msg();
	if(data_init(&data))
		return (1);
	
	start(&data);
}
