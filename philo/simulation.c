/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:43:08 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:36:36 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handel_one_philo(t_philo *philo)
{
	int	first;

	first = philo->left_fork;
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->data->forks[first]);
		print_message(philo, "has taken a fork");
		ft_usleep(philo, philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[first]);
		return (1);
	}
	return (0);
}

void	*philosopher_routine(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	if (handel_one_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo, philo->data->time_to_eat / 2);
	while (1)
	{
		if (set_dead(philo))
			break ;
		philosopher_eat(philo);
		if (set_dead(philo))
			break ;
		philosopher_sleep(philo);
		if (set_dead(philo))
			break ;
		philosopher_think(philo);
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
	int		full_count;

	data = (t_data *)argv;
	while (!data->someone_died)
	{
		i = 0;
		full_count = 0;
		while (i < data->number_of_philosophers)
		{
			if (check_philo_status(data, i, &full_count))
				return (NULL);
			i++;
		}
		if (data->meals_required > 0
			&& full_count == data->number_of_philosophers)
			return (NULL);
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
