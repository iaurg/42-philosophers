/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/23 16:50:28 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_eat(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, "has taken a fork");
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->ts_last_meal = actual_time();
	ft_usleep(table->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->count_meals++;
}

static void philo_think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

static void philo_sleep(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	print_message(philo, "is sleeping");
	ft_usleep(table->time_to_sleep, philo);
}

void kill_the_one(t_philo *philo)
{
	t_table			*table;

	table = philo->table;

	pthread_mutex_lock(philo->fork_left);
	print_message(philo, "has taken a fork");
	usleep(table->time_to_die * 1000);
	print_message(philo, "died");
	table->philo_alive = FALSE;
}

void	*start_dinner(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table			*table;

	table = philo->table;

	if (table->number_of_philos == 1)
		kill_the_one(philo);
	if (philo->id % 2)
		usleep(1200 * 1000);
	philo->ts_last_meal = actual_time();
	while (table->times_must_eat != philo->count_meals && (table->philo_alive != 0 && philo->is_alive != 0))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return NULL;
}

int	init_threads(t_table *table)
{
	int i;

	i = -1;
	while(++i < table->number_of_philos)
		pthread_create(&table->philos[i]->thread, NULL, start_dinner, table->philos[i]);
	i = -1;
	while(++i < table->number_of_philos)
		pthread_join(table->philos[i]->thread, NULL);
	return (SUCCESS);
}
