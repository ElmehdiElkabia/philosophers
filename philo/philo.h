/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:27:42 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_check_mutex;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}					t_philo;

int					validate_args(int argc, char **argv);
void				init_data(int argc, char **argv, t_data *data);
void				init_forks_and_philosophers(t_data *data);
void				start_simulation(t_data *data);
void				*philosopher_routine(void *arg);
void				*monitor_routine(void *arg);
void				someone_died(t_data *data, int i);
int					set_dead(t_philo *philo);
int					check_philo_status(t_data *data, int i, int *full_count);
void				print_msg(char *str);
void				print_message(t_philo *philo, char *message);
long long			ft_arg(const char *str);
long long			get_time(void);
void				philosopher_sleep(t_philo *philo);
void				philosopher_eat(t_philo *philo);
void				philosopher_think(t_philo *philo);
void				ft_usleep(t_philo *philo, long duration_ms);
#endif
