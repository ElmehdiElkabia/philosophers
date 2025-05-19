/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:19:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/05/19 14:31:14 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	wait_for_exit(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (pid != -1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (data->pids[i] != pid)
				kill(data->pids[i], SIGKILL);
			i++;
		}
	}
}
