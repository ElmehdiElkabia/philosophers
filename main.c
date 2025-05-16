/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/16 11:31:34 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_number(char *str)
{
	int i;

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

int validate_args(int argc, char **argv)
{
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: \
				%s number_of_philosophers time_to_die time_to_eat \
				 time_to_sleep[must_eat]\n ",
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
					time_to_sleep[must_eat]\n ",
				   argv[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

void init_forks_and_philosophers(t_data *data)
{
	int i;

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

long long get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void init_data(int argc, char **argv, t_data *data)
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
	data->start_time = get_time();
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_check_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->forks || !data->philo)
		perror("");
	init_forks_and_philosophers(data);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->death_check_mutex);
	int died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_check_mutex);
	
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!died)
		printf("%lld %d %s\n", get_time() - philo->data->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void *philo_routine(void *argv)
{
	t_philo *philo = (t_philo *)argv;
	
	pthread_mutex_lock(&philo->data->death_check_mutex);
	int died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_check_mutex);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!died)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (!died)
			print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (!died)
			print_message(philo, "has taken a fork");

		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);

		if (!died)
			print_message(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);

		if (died)
			break;

		if (!died)
			print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);

		if (died)
			break;

		if (!died)
			print_message(philo, "is thinking");

		if (philo->data->meals_required > 0 && philo->meals_eaten >= philo->data->meals_required)
			break;
	}
	return (NULL);
}

void *monitor(void *argv)
{
	t_data *data;
	int i;

	data = (t_data *)argv;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->philo[i].meal_mutex);
			if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
			{
				print_message(&data->philo[i], "died");
				pthread_mutex_lock(&data->death_check_mutex);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_check_mutex);
				pthread_mutex_unlock(&data->philo[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}

void start_simulation(t_data *data)
{
	int i;
	pthread_t monitor_thread;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int main(int argc, char **argv)
{
	t_data data;

	if (validate_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	start_simulation(&data);
	free(data.forks);
	free(data.philo);
}

// i = 0;
// printf("number_of_philosophers ==> %d\n", data.number_of_philosophers);
// while (i < data.number_of_philosophers)
//{
//	printf("id => %d  == time_to_die ==> %d\n", data.philo[i].id,
//		data.time_to_die);
//	printf("id => %d  == time_to_sleep ==> %d\n", data.philo[i].id,
//		data.time_to_sleep);
//	printf("id => %d  == time_to_eat ==> %d\n", data.philo[i].id,
//		data.time_to_eat);
//	printf("id => %d  == meals_required ==> %d\n", data.philo[i].id,
//		data.meals_required);
//	printf("id => %d  == left_fork ==> %d\n", data.philo[i].id,
//		data.philo[i].left_fork);
//	printf("id => %d  == right_fork ==> %d\n", data.philo[i].id,
//		data.philo[i].right_fork);
//	printf("id => %d  == last_meal_time ==> %lld\n", data.philo[i].id,
//		data.philo[i].last_meal_time);
//	printf("\n");
//	i++;
// }