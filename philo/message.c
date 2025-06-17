/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:20:18 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:28:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_msg(char *str)
{
	printf("Usage: %s number_of_philosophers ", str);
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]");
}
