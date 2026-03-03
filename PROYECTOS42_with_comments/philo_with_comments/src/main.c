#include "../philo.h"

/* INICIALIZAR LA SIMULACION,
	esta función se encarga de inicializar la estructura de datos,
	los filosofos y los mutex necesarios para la simulacion */
static int	init_sim(t_data *data, t_philo **philos, int argc, char **argv)
{
	int	i;

	// INICIALIZAR LOS VALORES DE LA ESTRUCTURA DE DATOS
	if (init_data(data, argc, argv))
		return (1);
	// INICIALIZAR LOS FILOSOFOS
	if (init_philos(data, philos))
		return (1);
	// inicializamos el mutex de la impresora y el mutex del estado de la simulacion
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	/* guardamos el momento en que se inicia la simulacion,
		esto se usa para calcular el tiempo transcurrido desde el inicio de la simulacion y para detectar la muerte de los filosofos */
	data->start_time = get_time_in_ms();
	/* establecemos el flag de la simulacion en curso,
		esto se usa para que los hilos de los filosofos y el hilo de monitoreo puedan terminar cuando sea necesario */
	data->simulation_running = 1;
	i = 0;
	/* inicializamos el tiempo de la ultima comida de cada filosofo */
	while (i < data->nb_philo)
	{
		(*philos)[i].last_meal = data->start_time;
		pthread_mutex_init(&(*philos)[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

/* Esta función inicia los hilos de los filósofos */
static int	start_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	/* Creamos los hilos de los filósofos */
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (1);
		i++;
	}
	/* Creamos el hilo del monitor */
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, philos))
		return (1);
	i = 0;
	/* Esperamos a que los hilos de los filósofos terminen */
	while (i < data->nb_philo)
		pthread_join(philos[i++].thread, NULL);
	/* Esperamos a que el hilo del monitor termine */
	pthread_join(data->monitor_thread, NULL);
	return (0);
}

/* Esta función libera los recursos utilizados por la simulación */
static void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	/* Destruimos los mutex de los tenedores */
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	// Destruimos los mutex de la impresora y el mutex del estado de la simulacion
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	// liberamos la memoria de los tenedores y los filosofos
	free(data->forks);
	free(philos);
}

int	main(int argc, char *argv[])
{
	t_data data;
	t_philo *philos;

	/* INICIALIZAR LA SIMULACION */
	if (init_sim(&data, &philos, argc, argv))
		return (1);
	/* INICIAR LOS HILOS DE LOS FILOSOFOS */
	if (start_threads(&data, philos))
	{
		/* Si ocurre un error al iniciar los hilos,
			limpiamos los recursos y salimos con error */
		cleanup(&data, philos);
		return (1);
	}
	// Si todo ha ido bien, limpiamos los recursos y salimos con éxito
	cleanup(&data, philos);
	return (0);
}