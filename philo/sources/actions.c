/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/25 22:42:32 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	t_table			*table;
	long			print_time;

	table = philo->table;
	print_time = actual_time() - table->ts_start;
	pthread_mutex_lock(&table->message);
	if (table->philo_alive != 0)
		printf("%5ld %d %s\n", print_time, philo->id + 1, msg);
	pthread_mutex_unlock(&table->message);
}
