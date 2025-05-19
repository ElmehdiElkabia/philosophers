/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:12:57 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/19 14:33:16 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_number(char *str)
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

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: \
				%s number_of_philosophers time_to_die time_to_eat \
				time_to_sleep[must_eat]\n ", argv[0]);
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
					time_to_sleep[must_eat]\n ", argv[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	start_simulation(&data);
}
