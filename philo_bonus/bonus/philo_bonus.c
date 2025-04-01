#include "philo_bonus.h"

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
		dinner_routine();
	}
	
}
int	main(int argc , char **argv)
{
	t_data data;
	if(parsing(argc,argv,&data))
		return(1);
	if(init_data(&data))
		return(1);
	start_syc(&data);

}