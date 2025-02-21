/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:37:52 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/21 14:44:24 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *arg)
{
	int			flag;
	long long	val;

	val = ft_atoi(arg, &flag);
	if (val > __INT_MAX__ || val <= 0 || flag)
		return (1);
	return (0);
}

int	fill_data(t_data *d, char **argv, int meal, int flag)
{
	int	flagerr;

	if (check_args(argv[1]) || check_args(argv[2]) || check_args(argv[3])
		|| check_args(argv[4]))
	{
		printf("Erorr in args values :)\n");
		return (1);
	}
	d->philo_number = ft_atoi(argv[1], &flagerr);
	d->time_die = ft_atoi(argv[2], &flagerr);
	d->time_to_eat = ft_atoi(argv[3], &flagerr);
	d->time_to_sleep = ft_atoi(argv[4], &flagerr);
	if (meal < 0 && flag)
	{
		printf("meals are less than 0\n");
		return (1);
	}
	d->meal_num = meal;
	return (0);
}
