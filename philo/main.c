/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/01 19:02:51 by eelkabia         ###   ########.fr       */
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

int	validate_time(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atol(argv[i]) == 0)
			return (1);
		if (ft_atol(argv[i]) == -2147483648)
		{
			printf("Error: Argument %d is out of valid int range\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_msg(char *str)
{
	printf("Usage: %s number_of_philosophers ", str);
	printf("time_to_die ");
	printf("time_to_eat ");
	printf("time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]");
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		print_msg(argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (check_number(argv[i]) == 1)
		{
			printf("Error: Argument %d must be a positive number\n", i);
			print_msg(argv[0]);
			return (1);
		}
		i++;
	}
	if (validate_time(argc, argv))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	start_simulation(&data);
	free(data.forks);
	free(data.philo);
}
