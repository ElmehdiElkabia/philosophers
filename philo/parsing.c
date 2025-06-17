/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:23 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:51 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	validate_must_eat(char **argv)
{
	if (ft_arg(argv[5]) == 0)
		return (1);
	if (ft_arg(argv[5]) == -2147483648)
	{
		printf("Error: Argument 5 is out of valid int range\n");
		return (1);
	}
	return (0);
}

static int	validate_time(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc - 1)
	{
		if (ft_arg(argv[i]) <= 0)
		{
			printf("Error: Argument %d must be a positive number\n", i);
			return (1);
		}
		if (ft_arg(argv[i]) == -2147483648)
		{
			printf("Error: Argument %d is out of valid int range\n", i);
			return (1);
		}
		i++;
	}
	if (argc == 6)
	{
		if (validate_must_eat(argv))
			return (1);
	}
	return (0);
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
