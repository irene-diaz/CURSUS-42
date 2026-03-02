/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:23:37 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 14:21:24 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// INITIALIZE DATA STRUCTURE VALUES
int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->nb_philo = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (data->nb_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (printf("Invalid arguments\n"), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (0);
}

// INITIALIZE PHILOSOPHERS
int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		(*philos)[i].last_meal = 0;
		pthread_mutex_init(&(*philos)[i].meal_mutex, NULL);
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	return (0);
}
