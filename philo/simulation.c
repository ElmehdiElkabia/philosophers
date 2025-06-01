/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:43:08 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/01 17:17:52 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handel_one_philo(t_philo *philo)
{
	int	first;

	first = philo->left_fork;
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->data->forks[first]);
		print_message(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(&philo->data->forks[first]);
		return (1);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	int	first;
	int	second;
	int	temp;

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

void	*philosopher_routine(void *argv)
{
	t_philo	*philo;
	int		died;

	philo = (t_philo *)argv;
	if (handel_one_philo(philo))
			return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eating(philo);
		set_dead(philo, &died);
		if (died)
			break ;
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (died)
			break ;
		print_message(philo, "is thinking");
		usleep(500);
		if (philo->data->meals_required > 0
			&& philo->meals_eaten >= philo->data->meals_required)
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *argv)
{
	t_data	*data;
	int		i;

	data = (t_data *)argv;
	while (!data->someone_died)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->philo[i].meal_mutex);
			if (data->meals_required > 0
				&& (data->philo[i].meals_eaten >= data->meals_required))
				return (NULL);
			if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
			{
				someone_died(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philo[i].thread, NULL, philosopher_routine,
			&data->philo[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
