/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:45:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 12:35:21 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	someone_died(t_data *data, int i)
{
	print_message(&data->philo[i], "died");
	pthread_mutex_lock(&data->death_check_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_check_mutex);
}

void	print_message(t_philo *philo, char *message)
{
	long long	time;

	if (set_dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!set_dead(philo))
		printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	set_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data->death_check_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_check_mutex);
	return (died);
}

long long	ft_atol(const char *str)
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
