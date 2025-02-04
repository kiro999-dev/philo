/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:08:19 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/04 15:44:24 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mutex_init(pthread_mutex_t *mtx)
{
    if (pthread_mutex_init(mtx, NULL) !=0)
        return (printf("Erorr in init mutex\n"),1);
    return (0);
}