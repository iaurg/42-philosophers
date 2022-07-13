/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:03:24 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/12 22:06:01 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	start_dinner(t_table *table)
{
	int		i;
	pthread_t	threads[table->n_philosophers];
	int			*result;
	int			ret;

	i = -1;
	while (++i < table->n_philosophers)
	{
		ret = pthread_create(&threads[i], NULL, philosopher, &table->philosophers[i]);
		if (ret)
		{
			printf("Error: pthread_create() failed\n");
			return (1);
		}
	}
	i = -1;
	while (++i < table->n_philosophers)
	{
		ret = pthread_join(threads[i], (void *)&result);
		if (ret)
		{
			printf("Error: pthread_join() failed\n");
			return (1);
		}
	}
	return (0);
}
