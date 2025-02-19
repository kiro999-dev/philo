#include "philo.h"

void eating(t_philo *p)
{
	pthread_mutex_lock(&p->fork1->fork);
	if(!is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
	{
		pthread_mutex_unlock(&p->fork1->fork);
		return;
	}
	write_status(p,take_fork);
	pthread_mutex_lock(&p->fork2->fork);
	write_status(p,take_fork);
	write_status(p,eat);
	pthread_mutex_lock(&p->data->check_mtx);
	if(!p->isfull)
		p->meal_count++;
	p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->data->check_mtx);
	ft_usleep(p->data->time_to_eat,p->data);
	pthread_mutex_unlock(&p->fork1->fork);
	pthread_mutex_unlock(&p->fork2->fork);
	
}
void thinking(t_philo *p)
{
	write_status(p,thinks);
}
void sleeping(t_philo *p)
{
	write_status(p,sleep);
	ft_usleep(p->data->time_to_sleep,p->data);
}
void* dinner(void *d)
{
	t_philo *p;

	p = (t_philo *) d;
	while (is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
	{
		pthread_mutex_lock(&p->data->check_mtx);
		if(p->isfull)
		{
			pthread_mutex_unlock(&p->data->check_mtx);
			break;
		}
		pthread_mutex_unlock(&p->data->check_mtx);
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return(NULL);
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
	check_sum(d);
	i = 0;
	while (i < d->philo_number)
	{
		if(pthread_join(d->philo_class[i].philos_t,NULL) != 0)
			return;
		i++;
	}
	
}