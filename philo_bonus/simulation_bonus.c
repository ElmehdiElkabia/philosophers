/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:57:57 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/19 14:29:38 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (1)
	{
		sem_wait(philo->data->meal_check);
		if (get_time() - philo->last_meal_time > philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%d died\n", philo->id);
			sem_post(philo->data->print);
			sem_post(philo->data->meal_check);
			exit(1);
		}
		sem_post(philo->data->meal_check);
		usleep(1000);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->data->fork);
	sem_wait(philo->data->fork);
	sem_wait(philo->data->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	sem_wait(philo->data->meal_check);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	printf("%lld %d is eating\n", get_time() - philo->data->start_time,
		philo->id);
	sem_post(philo->data->meal_check);
	sem_post(philo->data->print);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	philosopher_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philo);
		sem_wait(philo->data->print);
		printf("%lld %d is sleeping\n", get_time() - philo->data->start_time,
			philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		sem_post(philo->data->print);
		sem_wait(philo->data->print);
		printf("%lld %d is thinking\n", get_time() - philo->data->start_time,
			philo->id);
		usleep(500);
		sem_post(philo->data->print);
		if (philo->data->meals_required > 0
			&& philo->meals_eaten >= philo->data->meals_required)
			exit(0);
	}
}

void	start_simulation(t_data *data)
{
	int		i;
	t_philo	philo;

	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->pids)
		exit(1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
		{
			write(2, "fork failed\n", 13);
			exit(1);
		}
		if (data->pids[i] == 0)
		{
			init_philosopher(data, &philo, i);
			exit(0);
		}
		i++;
	}
	wait_for_exit(data);
}
