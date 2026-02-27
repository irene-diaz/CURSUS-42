#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (init_data(&data, argc, argv))
		return (1);
	if (init_philos(&data, &philos))
		return (1);
	// INICIALIZAR PRINT_MUTEX Y STATE_MUTEX
	pthread_mutex_init(&data.print_mutex, NULL);
	/* inicializamos el mutex para proteger simulation_running,
		ya que puede ser modificado por el hilo de monitoreo y leído por los hilos de los filosofos */
	pthread_mutex_init(&data.state_mutex, NULL);
	/* obtenemos el tiempo de inicio de la simulacion,
		esto es necesario para calcular el tiempo transcurrido y detectar la muerte de los filosofos */
	data.start_time = get_time_in_ms();
	// la simulacion empieza en curso, por lo que simulation_running es 1
	data.simulation_running = 1;
	// Inicializar mutex last_meal y setear last_meal a start_time
	i = 0;
	while (i < data.nb_philo)
	{
		// el tiempo de la ultima comida es el inicio de la simulacion
		philos[i].last_meal = data.start_time;
		// inicializamos el mutex para proteger last_meal,
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	/*creamos un hilo para cada filosofo,
		que ejecuta la rutina de los filosofos*/
	i = 0;
	while (i < data.nb_philo)
	{
		/* Creamos el hilo del filosofo,
			que ejecuta la rutina del filosofo y le pasamos su estructura */
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	/* Creamos el hilo de monitoreo,
			que ejecuta la rutina de monitoreo y le pasamos el array de filosofos para que pueda acceder a su estado */
	pthread_create(&data.monitor_thread, NULL, monitor_routine, philos);
	/*esperamos a que todos los hilos de los filosofos terminen,
		esto es necesario para evitar que el programa termine antes de que los filosofos impriman su estado*/
	i = 0;
	while (i < data.nb_philo)
		pthread_join(philos[i++].thread, NULL);
	// Esperamos a que el hilo de monitoreo termine
	pthread_join(data.monitor_thread, NULL);
	// Destruir los mutex de los tenedores antes de salir
	i = 0;
	while (i < data.nb_philo)
		pthread_mutex_destroy(&data.forks[i++]);
	// Destruir el mutex de print_mutex
	pthread_mutex_destroy(&data.print_mutex);
	// Destruir el mutex de state_mutex
	pthread_mutex_destroy(&data.state_mutex);
	// Liberar la memoria de los tenedores
	free(data.forks);
	// Liberar la memoria de los filosofos
	free(philos);
	/*printf("nb_philo: %d\n", data.nb_philo);
	printf("time_to_die: %ld\n", data.time_to_die);
	printf("time_to_eat: %ld\n", data.time_to_eat);
	printf("time_to_sleep: %ld\n", data.time_to_sleep);*/
	return (0);
}
