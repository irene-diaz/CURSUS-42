/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:24:17 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 10:24:18 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* This function initializes the simulation */
static int	init_sim(t_data *data, t_philo **philos, int argc, char **argv)
{
	int	i;

	if (init_data(data, argc, argv))
		return (1);
	if (init_philos(data, philos))
		return (1);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	data->start_time = get_time_in_ms();
	data->simulation_running = 1;
	i = 0;
	while (i < data->nb_philo)
	{
		(*philos)[i].last_meal = data->start_time;
		pthread_mutex_init(&(*philos)[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

/*This function starts the philosopher threads*/
static int	start_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, philos))
		return (1);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(philos[i++].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
	return (0);
}

/*This function cleans up the simulation*/
static void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	free(data->forks);
	free(philos);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (init_sim(&data, &philos, argc, argv))
		return (1);
	if (start_threads(&data, philos))
	{
		cleanup(&data, philos);
		return (1);
	}
	cleanup(&data, philos);
	return (0);
}
