/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:45:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/31 13:13:07 by eelkabia         ###   ########.fr       */
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
	pthread_mutex_unlock(&data->philo[i].meal_mutex);
}

void	print_message(t_philo *philo, char *message)
{
	int			died;
	long long	time;

	pthread_mutex_lock(&philo->data->death_check_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_check_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!died)
		printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

#include <limits.h>

// long	ft_atoi(const char *str)
// {
// 	int i;
// 	int sign;
// 	long result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = result * 10 + (str[i] - '0');
// 		if (result * sign > INT_MAX)
// 			return (INT_MAX + 1L);
// 		if (result * sign < INT_MIN)
// 			return (INT_MIN - 1L);
// 		i++;
// 	}
// 	return (result * sign);
// }

long    ft_atoi(char *s)
{
    long    res;
    int        i;

    i = 0;
    res = 0;
    if (s[i] == '+')
        i++;
    while (s[i])
    {
        res = (res * 10) + s[i] - '0';
        if (res > 2147483647)
            return (21474836479);
        i++;
    }
    if (!res)
        return (21474836479);
    return (res);
}