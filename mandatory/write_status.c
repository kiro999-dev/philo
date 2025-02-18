#include "philo.h"
void write_status(t_philo *p, int status)
{
	size_t elapsed;

 	pthread_mutex_lock(&p->data->philo_mtx);
	elapsed = get_current_time() - p->data->start_time;
	if(status == eat && is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
		printf("%ld %d is eating\n",elapsed,p->philo_id);
	if(status == die && is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
		printf("%ld %d died\n",elapsed,p->philo_id);
	if(status == take_fork && is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
		printf("%ld %d has taken a fork\n",elapsed,p->philo_id);
	if(status == sleep && is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
		printf("%ld %d is sleeping\n",elapsed,p->philo_id);
	if(status == thinks && is_not_finsh(&p->data->finsh_mtx,&p->data->isfinsh))
		printf("%ld %d is thinking\n",elapsed,p->philo_id);
	pthread_mutex_unlock(&p->data->philo_mtx);
}
