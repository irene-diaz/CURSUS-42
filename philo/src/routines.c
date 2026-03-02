/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:34:06 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 10:34:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Simulate philosophers' behavior

/* This function simulates a philosopher's behavior, specifically eating */
static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// Check if the simulation is still running in a thread-safe way
static int	is_running(t_data *data)
{
	int	r;

	pthread_mutex_lock(&data->state_mutex);
	r = data->simulation_running;
	pthread_mutex_unlock(&data->state_mutex);
	return (r);
}

/* Handle the case when there is only one philosopher,
	(he can only take one fork and will eventually die) */
static void	handle_single(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

// Philosopher routine
// This function runs in each philosopher thread and simulates its behavior
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		handle_single(philo);
		return (NULL);
	}
	while (is_running(philo->data))
	{
		eat(philo);
		if (!is_running(philo->data))
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (!is_running(philo->data))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}
