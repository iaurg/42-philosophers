/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:45:29 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/16 16:58:50 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc, char *argv[])
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_alive = TRUE;
	table->philo_feeding = TRUE;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->number_of_philos);
	if (argc == 6)
		table->times_must_eat = ft_atoi(argv[5]);
	else
		table->times_must_eat = -1;
}

static int	init_philos(t_table *table)
{
	int i;
	t_philo *philo;

	i = table->number_of_philos;
	if (!table)
		return (ERROR);
	while (--i >= 0)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (ERROR);
		philo->id = i;
		philo->count_meals = 0;
		philo->fork_left = &table->forks[i];
		philo->fork_right = &table->forks[(i + 1) % table->number_of_philos];
		philo->ts_last_meal = 0;
		philo->thread = 0;
		philo->is_alive = TRUE;
		philo->table = table;
		table->philos[i] = philo;
	}
	return (SUCCESS);
}

static int	init_mutex(t_table *table)
{
	int	i;

	if (!table)
		return (ERROR);
	i = table->number_of_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (ERROR);
	}
	return (SUCCESS);
}

int init_program(t_table *table, int argc, char *argv[])
{
	init_table(table, argc, argv);
	if (init_mutex(table))
		return (printf("Error while initializing mutexes!!\n"), 3);
	if (init_philos(table))
		return (printf("Error while initializing philosophers!!\n"), 4);
	return (SUCCESS);
}
