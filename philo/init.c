#include "philo.h"

/*Esta funcion prepara la mesa antes de sentar a los filósofos.
Concretamente:
1️⃣ Guarda el tiempo de inicio
2️⃣ Inicializa flags
3️⃣ Reserva los tenedores
4️⃣ Inicializa los mutex*/
int	init_data(t_data *data)
{
	int	i;

	// guardamos el timestamp de inicio de la simulacion,se usa para calcular el tiempo transcurrido y para detectar la muerte de los filosofos
	data->start_time = get_time();
	// inicializamos el flag de muerte a 0,la simulacion empieza con todos los filosofos vivos
	data->someone_died = 0;
	// reservamos memoria para el array de mutex que representan los tenedores,cada tenedor es un mutex que solo puede ser tomado por un filosofo a la vez
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	// inicializamos cada mutex del array de tenedores,esto convierte cada tenedor en un candado real
	while (i < data->nb_philo)
	{
		// si falla la inicializacion de algun mutex,devolvemos 1 para indicar error
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	// inicializamos el mutex de impresion(print_mutex),esto se usa para sincronizar la salida por pantalla,evitando que los mensajes de diferentes filosofos se mezclen
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	return (0);
}
/*Esta funcion:
1️⃣ Reserva memoria para los filósofos
2️⃣ Inicializa cada filósofo
3️⃣ Les asigna sus tenedores
4️⃣ Les da acceso a t_data
*/
int	init_philos(t_data *data, t_philo **philos)
{
	int i;

	// reservamos memoria para el array de filosofos
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		// asignamos un id a cada filosofo,esto se usa para identificarlo y para asignarle sus tenedores
		(*philos)[i].id = i;
		/*inicializamos el tiempo de la ultima comida al tiempo de inicio de la simulacion,
			esto se usa para detectar la muerte,
			si un filosofo no ha comido desde el inicio y el tiempo transcurrido supera time_to_die,entonces muere
		*/
		(*philos)[i].last_meal = data->start_time;
		// inicializamos el numero de comidas realizadas a 0,esto se actualizara cada vez que el filosofo coma,y se usara para detectar si ha alcanzado el limite de comidas(must_eat)
		(*philos)[i].meals_eaten = 0;
		// damos a cada filosofo acceso a la estructura compartida de la mesa,esto se usa para que puedan acceder a los parametros globales y a los tenedores
		(*philos)[i].data = data;

		// asignamos a cada filosofo sus tenedores,el tenedor de la izquierda es el que tiene el mismo indice que el filosofo
		(*philos)[i].left_fork = &data->forks[i];
		// y el tenedor de la derecha es el siguiente en el array,con modulo para que el ultimo filosofo tenga como tenedor derecho al primero
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	return (0);
}