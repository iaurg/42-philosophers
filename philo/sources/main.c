/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:46:30 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/14 21:05:11 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}

int	check_inputs(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo [number of philosophers] [time to eat]");
		printf(" [time to sleep] [time to die] [number of times to eat]\n");
		return (ERROR);
	}
	while (--argc > 0)
		if (ft_atoi(argv[argc]) < 0 || not_only_digits(argv[argc]))
			return (printf("Parameters must be positive numbers!\n"), ERROR);
	return (SUCCESS);
}
/*
Each philosopher should be a thread.

Each fork should be a mutex.

Each philosopher should have a unique fork to his left and to his right.

If there's only one philosopher, there should be only one fork on the table
*/

int	main(int argc, char *argv[])
{
	t_table	table;

	if (check_inputs(argc, argv))
		return (ERROR);
	if (init_program(&table, argc, argv))
		return (2);
	init_threads(&table);
	return (0);
}
