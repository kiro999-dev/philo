/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/18 12:18:15 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int is_finsh(pthread_mutex_t *mtx,int isfinsh)
{
	int val;
	
	pthread_mutex_lock(mtx);
	val = isfinsh;
	pthread_mutex_unlock(mtx);
	return(val);
}

void finish(t_data *d)
{
	pthread_mutex_lock(&d->finsh_mtx);
	d->isfinsh = 1;
	pthread_mutex_unlock (&d->finsh_mtx);
}

int check_philo(t_philo *philo)
{
	size_t elapsed;
	pthread_mutex_lock(&philo->data->check_mtx);
	if(philo->last_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check_mtx);
		return (0);
	}
	elapsed = get_current_time()- philo->last_eat; 
	if(elapsed > philo->data->time_die)
	{
		finish(philo->data);
		printf("%ld %d is died\n",get_current_time() - philo->data->start_time,philo->philo_id);
		pthread_mutex_unlock(&philo->data->check_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_mtx);
	return (0);
}

void check_sum(t_data *d)
{
	int i;

	i = 0;
	while (!is_finsh(&d->finsh_mtx,d->isfinsh))
	{
		i = 0;
		while (!is_finsh(&d->finsh_mtx,d->isfinsh) && i < d->philo_number)
		{
			if(check_philo(&d->philo_class[i]))
			{
				break;
			}
			i++;
		}
	}
}
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
	
	if(is_finsh(&p->data->finsh_mtx,p->data->isfinsh))
		return;
	pthread_mutex_lock(&p->data->philo_mtx);
	time = get_current_time() - p->data->start_time;
	printf("%ld %d is sleeping\n",time,p->philo_id);
	pthread_mutex_unlock(&p->data->philo_mtx);

}
void eating(t_philo *p)
{
	size_t timx;

	pthread_mutex_lock(&p->fork1->fork);
	if(is_finsh(&p->data->finsh_mtx,p->data->isfinsh))
		return;
	timx = get_current_time() - p->data->start_time;
	printf("%ld %d take fork %d\n",timx,p->philo_id,p->fork1->fork_id);
	pthread_mutex_lock(&p->fork2->fork);
	timx = get_current_time() - p->data->start_time;
	
	printf("%ld %d take fork %d\n",timx,p->philo_id,p->fork2->fork_id);
	printf("%ld %d eating\n",timx,p->philo_id);
	p->last_eat = get_current_time();
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(&p->fork1->fork);
	pthread_mutex_unlock(&p->fork2->fork);
	
}
void thinking(t_philo *p)
{
	size_t time;
	if(is_finsh(&p->data->finsh_mtx,p->data->isfinsh))
		return;
	pthread_mutex_lock(&p->data->philo_mtx);
	time = get_current_time() - p->data->start_time;
	printf("%ld %d is thinking\n",time,p->philo_id);
	pthread_mutex_unlock(&p->data->philo_mtx);
}
void* dinner(void *d)
{
	t_philo *p;

	p = (t_philo *) d;
	while (!is_finsh(&p->data->finsh_mtx,p->data->isfinsh))
	{
		eating(p);
		sleeping(p);
		ft_usleep(p->data->time_to_sleep);
		thinking(p);
	}
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
	
	check_sum(d);
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
