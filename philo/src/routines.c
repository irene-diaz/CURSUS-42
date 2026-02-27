#include "../philo.h"

// SIMULAR EL COMPORTAMIENTO DE LOS FILOSOFOS

/*Esta funcion simula el comportamiento de un filosofo, en especifico de comer*/
static void	eat(t_philo *philo)
{
	/* Para evitar el interbloqueo,
		los filosofos con id par toman primero el tenedor de la derecha y luego el de la izquierda,
		mientras que los filosofos con id impar hacen lo contrario */
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
	/* bloqueamos el mutex para proteger el acceso a last_meal,
	ya que lo vamos a modificar*/
	pthread_mutex_lock(&philo->meal_mutex);
	/* actualizamos el tiempo de la ultima comida,
	esto es necesario para que el hilo de monitoreo pueda detectar la muerte */
	philo->last_meal = get_time_in_ms();
	// desbloqueamos el mutex para permitir que el hilo de monitoreo pueda leer el tiempo de la ultima comida
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	/* Simulamos el tiempo que tarda en comer */
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// CREAR RUTINA DE LOS FILOSOFOS
/*Esta funcion se ejecuta en cada hilo de filosofo,
	simula su comportamiento y se encarga de imprimir su estado*/
/*utilizamos un puntero en vez de pasar la estructura completa,
	porque es más eficiente en términos de memoria y rendimiento*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Convertimos el puntero genérico a un puntero a t_philo para acceder a sus campos
	// printf("Philosopher %d is alive\n", philo->id);
	/* El bucle infinito simula el ciclo de vida del filosofo,
		que consiste en comer, dormir y pensar */
	while (1)
	{
		// Antes de cada acción, verificamos si la simulación sigue en curso,
		pthread_mutex_lock(&philo->data->state_mutex);
		/* Si la simulación ha terminado,
		desbloqueamos el mutex y salimos del bucle para terminar el hilo */
		if (!philo->data->simulation_running)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		// Si la simulación sigue en curso, desbloqueamos el mutex y continuamos
		pthread_mutex_unlock(&philo->data->state_mutex);
		eat(philo);
		/* Después de comer,
			verificamos nuevamente si la simulación sigue en curso antes de dormir y pensar */
		pthread_mutex_lock(&philo->data->state_mutex);
		/* Si la simulación ha terminado,
		desbloqueamos el mutex y salimos del bucle para terminar el hilo */
		if (!philo->data->simulation_running)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		// Si la simulación sigue en curso, desbloqueamos el mutex y continuamos
		pthread_mutex_unlock(&philo->data->state_mutex);
		// Simulamos el tiempo que tarda en dormir
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		/* Después de dormir,
			verificamos nuevamente si la simulación sigue en curso antes de pensar */
		pthread_mutex_lock(&philo->data->state_mutex);
		/* Si la simulación ha terminado,
		desbloqueamos el mutex y salimos del bucle para terminar el hilo */
		if (!philo->data->simulation_running)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		// Si la simulación sigue en curso, desbloqueamos el mutex y continuamos
		pthread_mutex_unlock(&philo->data->state_mutex);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
