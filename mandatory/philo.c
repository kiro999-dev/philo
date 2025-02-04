/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:52:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 09:56:00 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_data(t_data *d, char **argv, int meal)
{
	d->philo_number = ft_atoi(argv[1]);
	d->time_die = ft_atoi(argv[2]);
	d->time_to_sleep = ft_atoi(argv[3]);
	d->meal_num = meal;
}
void data_init(t_data *d)
{
	
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
	data_init(&data);
}