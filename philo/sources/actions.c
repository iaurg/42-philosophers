/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/19 22:27:21 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->message);
	printf("\033[0;32m");
	printf("[%5ld]\033[0m %d %s\n", actual_time() - table->ts_start, philo->id + 1, msg);
	pthread_mutex_unlock(&table->message);
}
