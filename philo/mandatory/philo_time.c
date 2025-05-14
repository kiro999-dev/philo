/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:30:43 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/08 20:45:02 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Erorr :gettimeofday()\n", 29);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time, t_data *d)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time
		&& is_not_finsh(&d->finsh_mtx, &d->isfinsh))
		usleep(500);
}
