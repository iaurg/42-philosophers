/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/26 06:46:49 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_dinner(void *arg)
{
	t_philo			*philo;
	t_table			*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->number_of_philos == 1)
		kill_the_one(philo);
	if (philo->id % 2 == 0)
		usleep(1500);
	philo->ts_last_meal = actual_time();
	while (table->times_must_eat != philo->count_meals
		&& table->philo_alive != FALSE)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	init_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		pthread_create(&table->philos[i]->thread, NULL, start_dinner,
			table->philos[i]);
	i = -1;
	while (++i < table->number_of_philos)
		pthread_join(table->philos[i]->thread, NULL);
	return (SUCCESS);
}
