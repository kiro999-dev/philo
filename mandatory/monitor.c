#include "philo.h"

int is_not_finsh(pthread_mutex_t *mtx,int *isfinsh)
{
	int val;
	
	pthread_mutex_lock(mtx);
	val = *isfinsh;
	pthread_mutex_unlock(mtx);
	return(val);
}

void finish(t_data *d)
{
	pthread_mutex_lock(&d->finsh_mtx);
	d->isfinsh = 0;
	pthread_mutex_unlock (&d->finsh_mtx);
}

int check_philo(t_philo *philo)
{
	size_t elapsed;
	
	pthread_mutex_lock(&philo->data->check_mtx);
	if (philo->last_eat == 0)
	{
		pthread_mutex_unlock(&philo->data->check_mtx);
		return (0);
	}
	elapsed = get_current_time()- philo->last_eat; 
	if(elapsed > philo->data->time_die && !philo->isfull)
	{
		write_status(philo,die);
		finish(philo->data);
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
	while (is_not_finsh(&d->finsh_mtx,&d->isfinsh))
	{
		i = 0;
		while (is_not_finsh(&d->finsh_mtx,&d->isfinsh) && i < d->philo_number)
		{
			if(check_philo(&d->philo_class[i]))
				break;
			i++;
		}
	}
}
