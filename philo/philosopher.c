/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:39:21 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:37:29 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
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
}

void	unlock_forks(t_philo *philo)
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
	pthread_mutex_unlock(&philo->data->forks[first]);
	pthread_mutex_unlock(&philo->data->forks[second]);
}

void	philosopher_eat(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	print_message(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo, philo->data->time_to_eat);
	unlock_forks(philo);
	ft_usleep(philo, 1);
}

void	philosopher_sleep(t_philo *philo)
{
	if (!set_dead(philo))
		print_message(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	philosopher_think(t_philo *philo)
{
	if (!set_dead(philo))
		print_message(philo, "is thinking");
	if (philo->data->number_of_philosophers % 2 != 0)
	{
		ft_usleep(philo, philo->data->time_to_eat / 2);
	}
	else if (philo->id % 2 == 0)
	{
		ft_usleep(philo, 1);
	}
}
