/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:42:02 by eelkabia            #+#    #+#             */
/*   Updated: 2025/06/14 23:42:03 by eelkabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philosopher_eat(t_philo *philo)
{
	int first;
	int second;
	int temp;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		temp = first;
		first = second;
		second = temp;
	}
	pthread_mutex_lock(&philo->data->forks[first]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	print_message(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[first]);
	pthread_mutex_unlock(&philo->data->forks[second]);
}

void philosopher_sleep(t_philo *philo)
{
	if (!set_dead(philo))
		print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void philosopher_think(t_philo *philo)
{

	if (!set_dead(philo))
		print_message(philo, "is thinking");
	usleep(500);
}
