/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/26 06:45:09 by itaureli         ###   ########.fr       */
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

void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	try_lock_mutex(philo);
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->ts_last_meal = actual_time();
	ft_usleep(table->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->count_meals++;
}

void	philo_think(t_philo *philo)
{
	print_message(philo, "is thinking");
	usleep(1200);
}

void	philo_sleep(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	print_message(philo, "is sleeping");
	ft_usleep(table->time_to_sleep, philo);
}

void	kill_the_one(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, "has taken a fork");
	usleep(table->time_to_die * 1000);
	print_message(philo, "died");
	table->philo_alive = FALSE;
}
