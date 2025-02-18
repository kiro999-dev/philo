#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void ft_usleep(size_t time,t_data *d)
{
	size_t start;

	if(!is_not_finsh(&d->finsh_mtx,&d->isfinsh))
		return;
	start = get_current_time();
	while ((get_current_time() - start )< time)
	{
		usleep(500);
	}
}