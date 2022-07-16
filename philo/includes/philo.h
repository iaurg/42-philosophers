/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:46:42 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/16 16:57:11 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/* external headers */
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* constants */
#define MAX_PHILOS 210
#define THINKING 0
#define EATING 1
#define SLEEPING 2
#define DIED 3
# define ERROR		1
# define SUCCESS	0
typedef enum {FALSE = 0, TRUE} boolean;

typedef pthread_mutex_t	t_mutex;

/* structs */
typedef struct s_table
{
	int times_must_eat;
	int number_of_philos;
	int philo_alive;
	int philo_feeding;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	long long ts_start;
	pthread_mutex_t *forks;
	struct s_philo **philos;
} t_table;

typedef struct s_philo
{
	int id;
	int count_meals;
	int is_alive;
	long long ts_last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t thread;
	t_table *table;
} t_philo;


/* startup */
int init_program(t_table *table, int argc, char *argv[]);
int	init_threads(t_table *table);

/* execution */
int think(t_table *table, int id);

/* utils */
int ft_atoi(const char *str);

#endif
