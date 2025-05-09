/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/09 11:29:26 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]

typedef	struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_required; //Optional argument: number of meals before simulation ends
	int	someone_died; //Flag (int) to stop the simulation if any philosopher dies.
	long	long	start_time;
	pthread_mutex_t	*forks; //Array of mutexes: one per fork. Forks are shared.
	pthread_mutex_t	print_mutex; //	Protects output (to avoid mixing messages).
	pthread_mutex_t	death_check_mutex; //Protects someone_died flag (avoids data races).
	struct	s_philo *philo; //	Array of t_philo, one per philosopher.
}	t_data;

typedef	struct s_philo
{
	int	id;
	int	meals_eaten; //Counter of meals eaten. Used for optional stop condition.
	int	left_fork; //	Index of left fork in data->forks
	int	right_fork; //	Index of right fork in data->forks
	long	long	last_meal_time; //	Timestamp of the last time this philosopher started eating.
	pthread_mutex_t	meal_mutex; //	Protects access to last_meal_time. Needed by monitor.
	t_data	*data; //	Pointer to shared t_data. Gives access to settings and mutexes.
}	t_philo;



#endif