/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:46:42 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/26 06:55:12 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* external headers */
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

/* constants */
# define MAX_PHILOS 210
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DIED 3
# define ERROR		1
# define SUCCESS	0
# define TRUE		1
# define FALSE		0

/* structs */
typedef struct s_table
{
	int				times_must_eat;
	int				number_of_philos;
	int				philo_alive;
	int				philo_feeding;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		ts_start;
	pthread_mutex_t	message;
	pthread_mutex_t	*forks;
	struct s_philo	**philos;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				count_meals;
	long int		ts_last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

/* startup */
int			init_program(t_table *table, int argc, char *argv[]);
int			init_threads(t_table *table);

/* execution */
int			think(t_table *table, int id);
void		print_message(t_philo *philo, char *msg);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		kill_the_one(t_philo *philo);

/* utils */
int			ft_atoi(const char *str);
long int	actual_time(void);
void		ft_usleep(int ms, t_philo *philo);
int			is_dead(t_philo *philo);
void		clean_up(t_table *table);
void		try_lock_mutex(t_philo *philo);
#endif
