/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/09 11:31:10 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: \
				%s number_of_philosophers time_to_die time_to_eat \
				 time_to_sleep[must_eat]\n ", \
				argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (check_number(argv[i]) == 1)
		{
			printf("Error: Argument %d must be a positive number\n", i);
			printf("Usage: \
					%s number_of_philosophers time_to_die time_to_eat \
					time_to_sleep[must_eat]\n ", \
					argv[0]);
			return (1);
		}
		i++;
	}
	return (0);
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
	data->someone_died = 0;
	data->start_time = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_check_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->forks || !data->philo)
		perror("");
	init_forks_and_philosophers(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (validate_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	i = 0;
	printf("number_of_philosophers ==> %d\n", data.number_of_philosophers);
	while (i < data.number_of_philosophers)
	{
		printf("id => %d  == time_to_die ==> %d\n", data.philo[i].id,
			data.time_to_die);
		printf("id => %d  == time_to_sleep ==> %d\n", data.philo[i].id,
			data.time_to_sleep);
		printf("id => %d  == time_to_eat ==> %d\n", data.philo[i].id,
			data.time_to_eat);
		printf("id => %d  == meals_required ==> %d\n", data.philo[i].id,
			data.meals_required);
		printf("id => %d  == left_fork ==> %d\n", data.philo[i].id,
			data.philo[i].left_fork);
		printf("id => %d  == right_fork ==> %d\n", data.philo[i].id,
			data.philo[i].right_fork);
		printf("id => %d  == last_meal_time ==> %lld\n", data.philo[i].id,
			data.philo[i].last_meal_time);
		printf("\n");
		i++;
	}
	free(data.forks);
	free(data.philo);
}
