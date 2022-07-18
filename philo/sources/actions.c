/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/17 21:08:12 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	t_table			*table;
	struct timeval	now;

	table = philo->table;
	pthread_mutex_lock(&table->message);
	gettimeofday(&now, NULL);
	printf("\033[0;32m");
	printf("[%5lld]\033[0m %d %s\n", gen_timestamp() - table->ts_start, philo->id + 1, msg);
	pthread_mutex_unlock(&table->message);
}
