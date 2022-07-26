/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:47:42 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/25 23:26:28 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_dead(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	if ((actual_time() - philo->ts_last_meal) > table->time_to_die)
	{
		print_message(philo, "died");
		table->philo_alive = FALSE;
		return (1);
	}
	return (0);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long	start_time;

	start_time = actual_time();
	while ((actual_time() - start_time) < (long) ms)
	{
		usleep(10);
		if (is_dead(philo))
			return ;
	}
}
