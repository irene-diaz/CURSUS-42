/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:12:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/02/27 13:47:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

/* ================= INCLUDES ================= */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/* ================= STRUCTS ================= */
//ESTRUCTURA DE LA MESA DE TRABAJO(compartida)
typedef struct s_data
{
    int             nb_philo; //nº de filosofos, lo que se traduce en nº de tenedores
    //tiempos en milisegundos, todos los filosofos usan los mismos tiempos
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;

    long            start_time; //momento en que se inicia la simulacion, se usa para calcular el tiempo transcurrido(timestamp)
    
	int				simulation_running; //flag para indicar si la simulacion sigue en curso, se usa para que el hilo de los filosofos y el hilo de monitoreo puedan terminar cuando sea necesario
	pthread_mutex_t	state_mutex; //mutex para proteger el acceso a simulation_running, ya que puede ser modificado por el hilo de monitoreo y leído por los hilos de los filosofos

    pthread_mutex_t *forks; //array de mutex para representar los tenedores, cada tenedor es un mutex que solo puede ser tomado por un filosofo a la vez
    pthread_mutex_t print_mutex; //mutex para sincronizar la salida por pantalla, evitando que los mensajes de diferentes filosofos se mezclen

    pthread_t		monitor_thread; //hilo que se encarga de monitorear la muerte de los filosofos, se ejecuta en paralelo a los hilos de los filosofos y verifica constantemente si alguno ha muerto por no haber comido a tiempo
}   t_data;

//ESTRUCTURA DE LOS FILOSOFOS(individual), esta estructura representa 1 hilo(1 filosofo)
typedef struct s_philo
{
    int             id; //identificador del filosofo, va de 0 a nb_philo-1
    pthread_t       thread; //el hilo real del sistema, se crea con pthread_create y se ejecuta la funcion que simula el comportamiento del filosofo

    pthread_mutex_t *left_fork; //tenedor de la izquierda
    pthread_mutex_t *right_fork; //tenedor de la derecha

    long            last_meal; //tiempo de la utlima comida, se usa para detectar la muerte
	pthread_mutex_t	meal_mutex; //mutex para proteger el acceso a last_meal, ya que puede ser modificado por el hilo del filosofo y leído por el hilo que monitorea la muerte
    
    t_data          *data; //puntero a la estructura compartida de la mesa, para acceder a los parametros globales y a los tenedores
}   t_philo;

/* ================= FUNCTIONS ================= */


/*utils lib*/
int     ft_atoi(const char *str);
long    ft_atol(const char *str);

/*utils*/
void	print_status(t_philo *philo, char *msg);
long	get_time_in_ms(void);
long	timestamp(t_data *data);

// init.c
int		init_data(t_data *data, int argc, char **argv);
int		init_philos(t_data *data, t_philo **philos);

/*routines*/
void	*philo_routine(void *arg);

/*monitor*/
void	*monitor_routine(void *arg);

#endif