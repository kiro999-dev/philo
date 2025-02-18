/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/18 10:50:41 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void ft_usleep(size_t time)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start )< time)
	{
		usleep(500);
	}
}

void sleeping(t_philo *p)
{
	size_t time;

	pthread_mutex_lock(&p->data->philo_mtx);
	time = get_current_time() - p->data->start_time;
	printf("%ld %d is sleeping\n",time,p->philo_id);
	pthread_mutex_unlock(&p->data->philo_mtx);

}
void eating(t_philo *p)
{
	size_t timx;

	pthread_mutex_lock(&p->fork1->fork);

	timx = get_current_time() - p->data->start_time;
	printf("%ld %d take fork %d\n",timx,p->philo_id,p->fork1->fork_id);
	pthread_mutex_lock(&p->fork2->fork);
	timx = get_current_time() - p->data->start_time;
	printf("%ld %d take fork %d\n",timx,p->philo_id,p->fork2->fork_id);
	printf("%ld %d eating\n",timx,p->philo_id);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(&p->fork1->fork);
	pthread_mutex_unlock(&p->fork2->fork);
	
}
void thinking(t_philo *p)
{
	size_t time;
	pthread_mutex_lock(&p->data->philo_mtx);
	time = get_current_time() - p->data->start_time;
	printf("%ld %d is thinking\n",time,p->philo_id);
	pthread_mutex_unlock(&p->data->philo_mtx);
}
void* dinner(void *d)
{
	t_philo *philos;

	philos = (t_philo *) d;
	eating(philos);
	sleeping(philos);
	ft_usleep(philos->data->time_to_sleep);
	thinking(philos);
	return(NULL);
}
void	fill_data(t_data *d, char **argv, int meal)
{
	d->philo_number = ft_atoi(argv[1]);
	d->time_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	d->meal_num = meal;
}
void check_philo(t_data *d)
{
	int i;

	i = 0;
	while (i < d->philo_number)
	{
		printf("philo : %d\n",d->philo_class[i].philo_id);
		i++;
	}
}
void creat_philos(t_data *d)
{
	int i;

	i = 0;
	d->start_time = get_current_time();
	while (i < d->philo_number)
	{
		if(pthread_create(&d->philo_class[i].philos_t,NULL, dinner, &d->philo_class[i]) != 0)
			return;
		i++;
	}
	i = 0;
	
	// check_philo(d);
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
		return (print_msg());
	if(data_init(&data))
		return (1);
	start(&data);
}
