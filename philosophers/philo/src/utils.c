/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:35:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/02 10:35:36 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* Return current time in milliseconds since the start of the simulation */
long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Return elapsed time since the start of the simulation */
long	timestamp(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}

/* Print the philosopher status in a thread-safe way */
void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->simulation_running)
		printf("%ld %d %s\n", timestamp(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
