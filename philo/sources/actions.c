/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/23 15:37:01 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->message);
	printf("%5ld %d %s\n", actual_time() - table->ts_start, philo->id + 1, msg);
	pthread_mutex_unlock(&table->message);
}
