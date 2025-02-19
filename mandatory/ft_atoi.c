/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:40 by zkhourba          #+#    #+#             */
/*   Updated: 2025/02/19 18:35:26 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	itssapce(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	skip(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && itssapce(s[i]))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			flag;
	long long	res;

	i = skip(str);
	res = 0;
	flag = 1;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > ((9223372036854775807 - (str[i] - '0')) / 10) && flag == -1)
			return (0);
		else if (res > ((9223372036854775807 - (str[i] - '0')) / 10)
			&& flag == 1)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res * flag);
}
