#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philo %d alive\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (ac < 5)
	{
		printf("Usage: ./philo nb_philo t_die t_eat t_sleep\n");
		return (1);
	}
	data.nb_philo = atoi(av[1]);
	data.time_to_die = atol(av[2]);
	data.time_to_eat = atol(av[3]);
	data.time_to_sleep = atol(av[4]);
	data.must_eat = -1;
	if (init_data(&data))
		return (1);
	if (init_philos(&data, &philos))
		return (1);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	destroy_all(&data, philos);
	return (0);
}
