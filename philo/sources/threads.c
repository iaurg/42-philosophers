/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/17 16:56:03 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_eat(t_philo *philo)
{
	t_table			*table;
	struct timeval	start;
	struct timeval	end;

	table = philo->table;
	gettimeofday(&start, NULL);
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->ts_last_meal = time_diff(&start, &end);
	print_message(philo, "has taken a fork");
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->count_meals = philo->count_meals + 1;
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	gettimeofday(&end, NULL);
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
	usleep(table->time_to_sleep * 1000);
}

void kill_the_one(t_philo *philo)
{
	t_table			*table;

	table = philo->table;

	pthread_mutex_lock(philo->fork_left);
	print_message(philo, "has taken a fork");
	print_message(philo, "died");
	table->philo_alive = FALSE;
}

void	*start_dinner(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table			*table;

	table = philo->table;

	// if 1 philo just die
	if(table->number_of_philos == 1)
		kill_the_one(philo);
	while(table->philo_alive)
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

	i = 0;
	while(i < table->number_of_philos)
	{
		if(pthread_create(&table->philos[i]->thread, NULL, start_dinner, table->philos[i]))
		{
			printf("Error creating thread\n");
			return (ERROR);
		}
		i++;
	}
	i = 0;
	while(i < table->number_of_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	return (SUCCESS);
}
