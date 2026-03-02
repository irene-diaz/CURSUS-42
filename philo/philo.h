/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:12:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 14:06:08 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ================= INCLUDES ================= */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ================= STRUCTS ================= */

/* Shared table structure */
typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;

	long			start_time;

	int				simulation_running;
	pthread_mutex_t	state_mutex;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;

	pthread_t		monitor_thread;
}					t_data;

/* Philosopher structure (individual) - represents one thread */
typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				meals_eaten;

	long			last_meal;
	pthread_mutex_t	meal_mutex;

	t_data			*data;
}					t_philo;

/* ================= FUNCTIONS ================= */

/*utils lib*/
int					ft_atoi(const char *str);
long				ft_atol(const char *str);

/*utils*/
void				print_status(t_philo *philo, char *msg);
long				get_time_in_ms(void);
long				timestamp(t_data *data);

// init.c
int					init_data(t_data *data, int argc, char **argv);
int					init_philos(t_data *data, t_philo **philos);

/*routines*/
void				*philo_routine(void *arg);

/*monitor*/
void				*monitor_routine(void *arg);

#endif