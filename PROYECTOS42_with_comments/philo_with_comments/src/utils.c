#include "../philo.h"

/* Devuelve el tiempo actual en milisegundos desde el inicio de la simulacion */
long	get_time_in_ms(void)
{
	struct timeval	tv;

	/* La función gettimeofday llena la estructura timeval con el tiempo actual,
		que incluye los segundos (tv_sec) y los microsegundos (tv_usec) desde el Epoch (1 de enero de 1970) */
	gettimeofday(&tv, NULL);
	// El tiempo se calcula como los segundos multiplicados por 1000 (para convertir a milisegundos) más los microsegundos divididos por 1000 (para convertir a milisegundos)
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Devuelve el tiempo transcurrido desde el inicio de la simulacion */
long	timestamp(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}

/* Imprime el estado del filosofo de forma sincronizada */
void	print_status(t_philo *philo, char *msg)
{
	/*utilizamos print_mutex para evitar que los mensajes se mezclen*/
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	/* Si la simulacion esta en curso, imprimimos el estado del filosofo */
	if (philo->data->simulation_running)
		printf("%ld %d %s\n", timestamp(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
