/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/20 23:02:32 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	died(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	table->philo_alive = FALSE;
	philo->is_alive = FALSE;
	print_message(philo, "died");
	return ;
}

static void philo_eat(t_philo *philo)
{
	t_table			*table;

	table = philo->table;

	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->ts_last_meal = actual_time();
	print_message(philo, "has taken a fork");
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->count_meals++;
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);

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
	ft_usleep(table->time_to_sleep);
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
		ft_usleep(table->time_to_eat / 10);
	while (table->times_must_eat != philo->count_meals && (table->philo_alive != 0 && philo->is_alive != 0))
	{
		philo_eat(philo);
		if ((actual_time() - philo->ts_last_meal) > table->time_to_die)
		{
			died(philo);
			ft_usleep(table->time_to_die);
			return (NULL);
		}
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
