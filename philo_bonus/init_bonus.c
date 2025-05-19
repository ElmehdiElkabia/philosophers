/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:14:59 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/19 14:31:47 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->meals_required = atoi(argv[5]);
	else
		data->meals_required = -1;
	data->start_time = get_time();
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/meal_check");
	data->fork = sem_open("/fork", O_CREAT, 0644, data->number_of_philosophers);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	data->meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);
	if (data->fork == SEM_FAILED || data->print == SEM_FAILED
		|| data->death == SEM_FAILED || data->meal_check == SEM_FAILED)
	{
		write(2, "sem_open failed\n", 16);
		exit(1);
	}
}

void	init_philosopher(t_data *data, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal_time = get_time();
	philo->data = data;
	pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo);
	pthread_detach(philo->monitor_thread);
	philosopher_routine(philo);
}
