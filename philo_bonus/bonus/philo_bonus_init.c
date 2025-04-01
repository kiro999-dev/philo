#include "philo_bonus.h"

void	write_status(t_philo_bonus *p, int status)
{
	size_t		elapsed;
	static int	f;

	sem_wait(p->data->message);
	elapsed = get_current_time() - p->data->start_time;
	if (f == 0)
		elapsed = 0;
	f++;
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
	if(status != DIE)
		sem_post(p->data->message);
}

void	ft_create_semaphores(t_data *d)
{
	sem_unlink("death");
	sem_unlink("message");
	sem_unlink("check");
	sem_unlink("forks");
	d->finish = sem_open("death", O_CREAT, 0600, 1);
	d->check = sem_open("check", O_CREAT, 0600, 1);
	d->message = sem_open("message", O_CREAT, 0600, 1);
	d->forks = sem_open("forks", O_CREAT, 0600,
			d->philo_number);
}
void	init_philo(t_data *d)
{
	int i;

	i = 0;
	while (i < d->philo_number)
	{
		d->philo_class[i].data = d;
		d->philo_class[i].philo_id = i+1;
		d->philo_class[i].isfull = 0;
		d->philo_class[i].meal_count = 0;
		d->philo_class[i].last_eat = 0;
		d->philo_class[i].pid = -1;
		i++;
	}
}

int init_data(t_data *d)
{
	d->philo_class = malloc(sizeof(t_philo_bonus) * d->philo_number);
	if (d->philo_class == NULL)
		return(1);
	init_philo(d);
    ft_create_semaphores(d);
	return(0);
}