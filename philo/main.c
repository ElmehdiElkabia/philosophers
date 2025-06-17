/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:37:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/06/17 14:21:46 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
