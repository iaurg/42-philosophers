/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:46:30 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/09 17:18:30 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int not_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int check_inputs(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat]");
		printf(" [time to sleep] [time to die] [number of times to eat]\n");
		return (1);
	}
	while (--argc > 0)
	{
		if (not_only_digits(argv[argc]))
			return (printf("Parameters must be numeric!!\n"), 2);
	}
	return (0);
}

/*
Each philosopher should be a thread.

Each fork should be a mutex.

Each philosopher should have a unique fork to his left and to his right.

If there's only one philosopher, there should be only one fork on the table
*/

int main(int argc, char *argv[])
{
	t_table table;

	if (check_inputs(argc, argv))
		return (1);
	if (init_program(&table, argc, argv))
		return (2);
	printf("THE PHILOSOPHERS DINNER\n");
	printf("Number of philosophers: %d\n", table.number_of_philos);
	printf("Time to eat: %d\n", table.time_to_eat);
	printf("Time to sleep: %d\n", table.time_to_sleep);
	printf("Time to die: %d\n", table.time_to_die);
	printf("Number of meals: %d\n", table.times_must_eat);
	return (0);
}
