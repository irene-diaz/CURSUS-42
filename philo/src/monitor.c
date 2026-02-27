#include "../philo.h"

// Rutina de monitoreo de los filósofos
void	*monitor_routine(void *arg)
{
	t_philo *philos;
	t_data *data;
	int i;

	// Convertimos el puntero genérico a un puntero a t_philo para acceder a sus campos
	philos = (t_philo *)arg;
	/* Obtenemos el puntero a la estructura de datos compartida desde el primer filósofo,
		ya que todos los filósofos tienen el mismo puntero a la estructura de datos compartida */
	data = philos[0].data;

	while (1)
	{
		i = 0;
		// Recorremos el array de filósofos para verificar si alguno ha muerto
		while (i < data->nb_philo)
		{
			// Bloqueamos el mutex de la última comida del filósofo para acceder a su valor de forma segura
			pthread_mutex_lock(&philos[i].meal_mutex);
			/* Si el tiempo actual menos el tiempo de la ultima comida es mayor o igual al tiempo de muerte,
			el filosofo ha muerto */
			if (get_time_in_ms() - philos[i].last_meal >= data->time_to_die)
			{
				// Desbloqueamos el mutex de la última comida del filósofo antes de imprimir su estado y terminar la simulación
				pthread_mutex_unlock(&philos[i].meal_mutex);
				// Bloqueamos el mutex de estado para verificar si la simulación sigue en curso
				pthread_mutex_lock(&data->state_mutex);
				/* Si la simulación sigue en curso,
					la terminamos y imprimimos el estado del filósofo muerto */
				if (data->simulation_running)
				{
					/* Si el filósofo ha muerto,
						establecemos simulation_running a 0 para indicar que la simulación ha terminado */
					data->simulation_running = 0;
					/* Desbloqueamos el mutex de estado después de modificarlo para permitir que los hilos de los filósofos puedan leer su valor y terminar si es necesario */
					pthread_mutex_unlock(&data->state_mutex);
					/* Bloqueamos el mutex de impresión para imprimir el estado del filósofo muerto de forma segura y evitar que los mensajes se mezclen */
					pthread_mutex_lock(&data->print_mutex);
					/* Imprimimos el estado del filósofo muerto */
					printf("%ld %d died\n", timestamp(data), philos[i].id);
					/* Desbloqueamos el mutex de impresión después de imprimir el estado del filósofo muerto */
					pthread_mutex_unlock(&data->print_mutex);
					return (NULL);
				}
				else
					/* Si la simulación ya ha terminado,
						desbloqueamos el mutex de estado y salimos del bucle para terminar el hilo de monitoreo */
					pthread_mutex_unlock(&data->state_mutex);
			}
			/* Si el filósofo no ha muerto,
				desbloqueamos el mutex de la última comida para permitir que el hilo del filósofo pueda modificar su valor y continuar con la simulación */
			else
				pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		/* Para evitar que el hilo de monitoreo consuma demasiados recursos al verificar constantemente el estado de los filósofos,
			podemos agregar un pequeño retraso antes de la siguiente verificación. Esto también permite que los hilos de los filósofos tengan tiempo para actualizar su estado y evitar condiciones de carrera. */
		usleep(1000);
	}
	return (NULL);
}