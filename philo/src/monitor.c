/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:29:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 16:55:52 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Handle philosopher death and print status
static int	handle_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_mutex);
	if (data->simulation_running)
	{
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", timestamp(data), philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

// Check for philosopher deaths
static int	check_deaths(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (get_time_in_ms() - philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (handle_death(data, &philos[i]))
				return (1);
		}
		else
			pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (0);
}

// Check if all philosophers have eaten enough times (if must_eat_count is set)
static int	all_ate_enough(t_data *data, t_philo *philos)
{
	int	i;
	int	finished;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	finished = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].meals_eaten >= data->must_eat_count)
			finished++;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	if (finished == data->nb_philo)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

// Monitor routine for philosophers
void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		if (check_deaths(data, philos))
			return (NULL);
		if (all_ate_enough(data, philos))
			return (NULL);
		pthread_mutex_lock(&data->state_mutex);
		if (!data->simulation_running)
		{
			pthread_mutex_unlock(&data->state_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->state_mutex);
		usleep(500);
	}
	return (NULL);
}
