/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:41:41 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/31 11:06:39 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->someone_died = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_check_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->forks || !data->philo)
		perror("");
	init_forks_and_philosophers(data);
}

void	init_forks_and_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->number_of_philosophers;
		data->philo[i].last_meal_time = data->start_time;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		i++;
	}
}
