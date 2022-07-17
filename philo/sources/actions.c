/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/17 16:04:01 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(struct timeval *start, struct timeval *end)
{
	long double	sec;
	long double	usec;

	sec = end->tv_sec - start->tv_sec;
	usec = end->tv_usec - start->tv_usec;
	return (sec * 1000 + usec / 1000);
}

void	print_message(t_philo *philo, char *msg)
{
	t_table			*table;
	struct timeval	now;

	table = philo->table;
	pthread_mutex_lock(&table->message);
	gettimeofday(&now, NULL);
	printf("\033[0;32m");
	printf("[%5ld]\033[0m %d %s\n", time_diff(&table->ts_start, &now), philo->id + 1, msg);
	pthread_mutex_unlock(&table->message);
}
