#include "../philo.h"

/* Manejar la muerte de un filósofo y imprimir su estado */
static int	handle_death(t_data *data, t_philo *philo)
{
	/* Bloquear el mutex de estado para acceder de forma segura a simulation_running */
	pthread_mutex_lock(&data->state_mutex);
	/* Verificar si la simulación sigue en curso */
	if (data->simulation_running)
	{
		/* Si la simulación sigue en curso,
			la terminamos y imprimimos el estado del filósofo muerto */
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", timestamp(data), philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	/* Si la simulación ya ha terminado, no hacemos nada */
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

/* mirar si algun filosofo ha muerto por no haber comido a tiempo, si es asi,
	terminar la simulacion y mostrar el mensaje de muerte,
	esta funcion se ejecuta constantemente en el hilo del monitor */
static int	check_deaths(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	/* Recorremos todos los filósofos */
	while (i < data->nb_philo)
	{
		/* Bloquear el mutex del filósofo para acceder de forma segura a last_meal */
		pthread_mutex_lock(&philos[i].meal_mutex);
		/* Verificar si el filósofo ha muerto */
		if (get_time_in_ms() - philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (handle_death(data, &philos[i]))
				return (1);
		}
		/* Si el filósofo está vivo, desbloquear el mutex */
		else
			pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (0);
}

/* Verificar si todos los filósofos han comido suficientes veces (si must_eat_count está establecido) */
static int	all_ate_enough(t_data *data, t_philo *philos)
{
	int	i;
	int	finished;

	/* Si no se ha establecido un número de comidas, no hacemos nada */
	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	finished = 0;
	/* Recorremos todos los filósofos */
	while (i < data->nb_philo)
	{
		/* Bloquear el mutex del filósofo para acceder de forma segura a meals_eaten */
		pthread_mutex_lock(&philos[i].meal_mutex);
		/* Verificar si el filósofo ha comido suficientes veces */
		if (philos[i].meals_eaten >= data->must_eat_count)
			finished++;
		/* Desbloquear el mutex del filósofo */
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	// Si todos los filósofos han comido suficientes veces,
	terminamos la simulación if (finished == data->nb_philo)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

/* Rutina de monitoreo para los filósofos */
void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	// El hilo del monitor recibe un puntero al array de filósofos como argumento
	philos = (t_philo *)arg;
	/* Obtenemos un puntero a la estructura de datos compartida desde el primer filósofo,
		ya que todos los filósofos tienen un puntero a la misma estructura de datos */
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
