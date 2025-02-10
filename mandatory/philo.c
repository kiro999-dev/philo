/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 18:51:15 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int wait_philos(t_philo *philos)
{
	if(philos->philo_vist == 0)
	{
		pthread_mutex_lock(&philos->data->philo_mtx);
		philos->philo_vist = 1;
	}
	if(philos->data->isready == philos->data->philo_number)
		return(0);
	else if(philos->philo_vist == 1)
	{
		philos->data->isready++;
		philos->philo_vist = 2;
		pthread_mutex_unlock(&philos->data->philo_mtx);
	}
	return(1);
}
// void sleeping(t_philo *p)
// {

// }
void eating(t_philo *p)
{
	pthread_mutex_lock(&p->fork1->fork);
	printf("%d take fork %d\n",p->philo_id,p->fork1->fork_id);
	pthread_mutex_lock(&p->fork2->fork);
	printf("%d take fork %d\n",p->philo_id,p->fork2->fork_id);
	printf("%d eating\n",p->philo_id);
	usleep(10000);
	pthread_mutex_unlock(&p->fork1->fork);
	pthread_mutex_unlock(&p->fork2->fork);
}
void* dinner(void *d)
{
	t_philo *philos;

	philos = (t_philo *) d;
 	while (wait_philos(philos))
	{
	}
	eating(philos);
	// sleeping(philos);
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
		if(pthread_create(&d->philo_class[i].philos_t,NULL, dinner, &d->philo_class[i]) != 0)
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
