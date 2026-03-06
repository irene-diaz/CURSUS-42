#include "../philo.h"

// INICIALIZAR LOS VALORES DE LA ESTRUCTURA DE DATOS
int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	/*validamos los argumentos, deben ser 4 argumentos: nº de filosofos,
	tiempo para morir, tiempo para comer y tiempo para dormir*/
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	/*si se especifica el número de veces que cada filósofo debe comer,
		lo guardamos en la estructura de datos, si no se especifica,
		lo dejamos en
			-1 para indicar que los filósofos pueden comer indefinidamente*/
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	/*inicializamos los valores de la estructura de datos*/
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	/*comprobamos que los argumentos sean validos,
		el nº de filosofos debe ser mayor a 0 y los tiempos deben ser mayores o iguales a 0*/
	if (data->nb_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	// CREAR TENEDORES
	/*reservamos memoria para los tenedores*/
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	/*inicializamos los mutex de los tenedores*/
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// printf("Forks initialized correctly\n");
	return (0);
}

// INICIALIZAR LOS FILOSOFOS
int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	/*reservamos memoria para los filosofos*/
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (1);
	/*inicializamos los valores de cada filosofo*/
	i = 0;
	/*recorremos el array de filosofos*/
	while (i < data->nb_philo)
	{
		/* El id del filosofo empieza en 1 para facilitar la lectura de los mensajes,
			aunque internamente se maneje como un array que empieza en 0 */
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		/* El tiempo de la última comida se inicializa en 0 */
		(*philos)[i].last_meal = 0;
		/* Inicializamos el mutex para proteger el acceso a last_meal,
		ya que puede ser modificado por el hilo del filosofo y leído por el hilo de monitoreo */
		pthread_mutex_init(&(*philos)[i].meal_mutex, NULL);
		// Cada filósofo coge el fork de la izquierda y la derecha
		(*philos)[i].left_fork = &data->forks[i];
		/* el tenedor de la derecha del ultimo filosofo es el primero,
			esto se logra con el operador modulo */
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	printf("Philosophers initialized correctly\n");
	return (0);
}
