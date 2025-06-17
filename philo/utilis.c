/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:45:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:34:57 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	ft_arg(const char *str)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i++] - '0');
		if (number > 2147483647)
			return (-2147483648);
	}
	return (number);
}

void	ft_usleep(t_philo *philo, long duration_ms)
{
	long	end_time;

	end_time = get_time() + duration_ms;
	while (get_time() < end_time)
	{
		if (set_dead(philo))
			break ;
		usleep(100);
	}
}
