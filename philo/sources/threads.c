/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/16 17:36:38 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_dinner(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	printf("Arg ID=%d \n", philo->id);
	if (philo->id % 2)
		usleep(1500);
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
		// wait until the thread is done before exit
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
