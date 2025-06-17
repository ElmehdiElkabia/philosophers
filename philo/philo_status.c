/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:22:05 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:28:35 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_status(t_data *data, int i, int *full_count)
{
	pthread_mutex_lock(&data->philo[i].meal_mutex);
	if (data->meals_required > 0
		&& (data->philo[i].meals_eaten >= data->meals_required))
		(*full_count)++;
	if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		someone_died(data, i);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].meal_mutex);
	return (0);
}

void	someone_died(t_data *data, int i)
{
	print_message(&data->philo[i], "died");
	pthread_mutex_lock(&data->death_check_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_check_mutex);
}

int	set_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data->death_check_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_check_mutex);
	return (died);
}
