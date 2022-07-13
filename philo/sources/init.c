/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:45:29 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/12 21:22:14 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_table(t_table *table, int argc, char *argv[])
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);

	table->philo_alive = 1;
	//- The philosophers must never be starving.
	table->philo_feeding = 1;
	if (argc == 6)
	{
		table->times_must_eat = ft_atoi(argv[5]);
		if (table->times_must_eat < 0)
			return (printf("Number of meals must be positive!!\n"), 1);
	}
	else
		table->times_must_eat = -1;
	return (0);
}

static int	init_philos(t_table *table)
{
	int i;

	i = table->number_of_philos;
	if (!table)
		return (1);
	while (--i >= 0)
	{
		table->philo[i].id = i;
		table->philo[i].count_meals = 0;
		table->philo[i].id_left_fork = i;
		table->philo[i].id_right_fork = (i + 1) % table->number_of_philos;
		table->philo[i].ts_last_meal = 0;
		table->philo[i].id_thread = 0;
	}
	return (0);
}

static int	init_mutex(t_table *table)
{
	int	i;

	if (!table)
		return (1);
	i = table->number_of_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (2);
	}
	return (0);
}

int init_program(t_table *table, int argc, char *argv[])
{
	if (init_table(table, argc, argv))
		return (1);
	if (init_mutex(table))
		return (printf("Error while initializing mutexes!!\n"), 3);
	if (init_philos(table))
		return (printf("Error while initializing philosophers!!\n"), 4);
	return (0);
}
