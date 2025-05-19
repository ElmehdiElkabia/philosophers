/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:57:36 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/19 13:08:28 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;

	long long	start_time;

	sem_t		*fork;
	sem_t		*print;
	sem_t		*death;
	sem_t		*meal_check;

	pid_t		*pids;

}				t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal_time;
	pthread_t	monitor_thread;
	t_data		*data;
}				t_philo;

void			init_data(int argc, char **argv, t_data *data);
long long		get_time(void);
void			*monitor_routine(void *argv);
void			start_simulation(t_data *data);
void			philosopher_routine(t_philo *philo);
void			wait_for_exit(t_data *data);
void			init_philosopher(t_data *data, t_philo *philo, int i);
void			init_data(int argc, char **argv, t_data *data);

#endif