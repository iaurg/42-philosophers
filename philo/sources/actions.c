/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:18:46 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/12 21:18:46 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int check_is_dead(t_table *table)
{
	if (table->philo_alive == 0)
		return (1);
	return (0);
}
