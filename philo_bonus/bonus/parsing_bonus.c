/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:08:31 by zkhourba          #+#    #+#             */
/*   Updated: 2025/04/07 13:18:24 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(char *arg)
{
	int			flag;
	long long	val;

	val = ft_atoi(arg, &flag);
	if (val > __INT_MAX__ || val <= 0 || flag)
		return (1);
	return (0);
}

int	fill_data(char **argv, t_data *d, int meal_num)
{
	int	flagerr;

	flagerr = 0;
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
	d->meal_num = meal_num;
	return (0);
}

int	parsing(int argc, char **argv, t_data *d)
{
	int	flagerr;

	flagerr = 0;
	if (argc == 5)
	{
		if (fill_data(argv, d, -1))
			return (1);
		else
			return (0);
	}
	else if (argc == 6)
	{
		if (check_args(argv[5]))
			return (1);
		if (fill_data(argv, d, ft_atoi(argv[5], &flagerr)))
			return (1);
		else
			return (0);
	}
	printf("try to enter like this 5 800 200 200 [X] :)\n4 or 5 args\n");
	return (1);
}
