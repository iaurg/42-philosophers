/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/17 21:11:32 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	died(t_philo *philo)
{
	t_table			*table;
	struct timeval	now;

	table = philo->table;
	printf("time ls_meal %lld \n", philo->ts_last_meal);
	printf("time to die %d \n", table->time_to_die);

	gettimeofday(&now, NULL);
	printf("\033[0;31m");
	printf("[%5lld]\033[0m %d died\n", gen_timestamp(), philo->id + 1);
	table->philo_alive = FALSE;
	philo->is_alive = FALSE;
	return (TRUE);

}

static void philo_eat(t_philo *philo)
{
	t_table			*table;
	struct timeval	start;
	struct timeval	end;

	table = philo->table;
	gettimeofday(&start, NULL);
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->ts_last_meal = gen_timestamp();
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

	if (table->number_of_philos == 1)
		kill_the_one(philo);
	if (philo->id % 2)
		usleep(1500);
	while (table->philo_alive != 0 && philo->is_alive != 0)
	{
		philo_eat(philo);
		if (died(philo))
			return NULL;
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
