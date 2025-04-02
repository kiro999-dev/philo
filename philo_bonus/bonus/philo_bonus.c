#include "philo_bonus.h"
void	ft_destroy_all(t_data *d, t_philo_bonus *philo)
{
	int	i;

	i = 0;
	while (i < d->philo_number)
		kill(philo[i++].pid, SIGKILL);
	sem_close(d->check);
	sem_close(d->message);
	sem_close(d->finish);
	sem_close(d->forks);
	free(philo);
}
void	*check_philos(void *data)
{
	t_philo_bonus *p;
	size_t elapsed;

	elapsed = 0;
	p = (t_philo_bonus *)data;
	while (1)
	{
		
		sem_wait(p->data->check);
		elapsed = get_current_time() - p->last_eat;
		if(elapsed > p->data->time_die && p->last_eat != 0)
		{
			write_status(p,DIE);
			sem_post(p->data->check);
			sem_post(p->data->finish);
			break;
		}
		sem_post(p->data->check);
		sem_wait(p->data->check);
		if(p->meal_count > p->data->meal_num)
		{
			sem_post(p->data->check);
			sem_post(p->data->finish);
			break;
		}
		sem_post(p->data->check);
	
	}
	return (NULL);
}
void	take_forks(t_philo_bonus *p)
{
	sem_wait(p->data->forks);
	write_status(p,TAKE_FORK);
	sem_wait(p->data->forks);
	write_status(p,TAKE_FORK);
}
void	eating(t_philo_bonus *p)
{
	sem_wait(p->data->check);
	write_status(p,EAT);
	p->meal_count++;
	p->last_eat = get_current_time();
	sem_post(p->data->check);
	ft_usleep(p->data->time_to_eat);
	sem_post(p->data->forks);
	sem_post(p->data->forks);
}
void	dinner_routine(t_philo_bonus *p)
{
	pthread_t pth;

	pthread_create(&pth,NULL,check_philos,p);
	pthread_detach(pth);
	while (1)
	{
		take_forks(p);
		eating(p);
		write_status(p,SLEEP);
		ft_usleep(p->data->time_to_sleep);
		write_status(p,THINKS);
	}
	
}
void start_syc(t_data *d)
{
	int i;

	i = 0;
	
	while (i < d->philo_number)
	{
		d->philo_class[i].pid = fork();
		if(d->philo_class[i].pid == -1)
		{
			printf("fork fail\n");
			return;
		}
		if(d->philo_class[i].pid == 0)
			dinner_routine(&d->philo_class[i]);
		i++;
		usleep(100);
	}
}
int	main(int argc , char **argv)
{
	t_data data;
	if(parsing(argc,argv,&data))
		return(1);
	if(init_data(&data))
		return(1);
	data.start_time = get_current_time();
	sem_wait(data.finish);
	start_syc(&data);
	sem_wait(data.finish);
	ft_destroy_all(&data,data.philo_class);

}