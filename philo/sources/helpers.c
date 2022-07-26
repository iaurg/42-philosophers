/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:45:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/26 06:45:35 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	clean_up(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		free(table->philos[i]);
	}
	pthread_mutex_destroy(&table->message);
	free(table->philos);
	free(table->forks);
	return ;
}

/*
Fake try lock to check if fork can be used
*/
void	try_lock_mutex(t_philo *philo)
{
	while (*(long *)philo->fork_left == 1 || *(long *)philo->fork_right == 1)
	{
		usleep(10);
		if (is_dead(philo))
			return ;
	}
}
