/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:12:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/02/08 14:20:45 by idiaz-ca         ###   ########.fr       */
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
    int             must_eat; //nº de veces que cada filosofo debe comer, si es -1, no hay limite

    long            start_time; //momento en que se inicia la simulacion, se usa para calcular el tiempo transcurrido(timestamp)
    int             someone_died; //flag global para indicar si algun filosofo ha muerto, se usa para detener la simulacion(cuando vale 1)

    pthread_mutex_t *forks; //array de mutex para representar los tenedores, cada tenedor es un mutex que solo puede ser tomado por un filosofo a la vez
    pthread_mutex_t print_mutex; //mutex para sincronizar la salida por pantalla, evitando que los mensajes de diferentes filosofos se mezclen
}   t_data;

//ESTRUCTURA DE LOS FILOSOFOS(individual), esta estructura representa 1 hilo(1 filosofo)
typedef struct s_philo
{
    int             id; //identificador del filosofo, va de 0 a nb_philo-1
    pthread_t       thread; //el hilo real del sistema, se crea con pthread_create y se ejecuta la funcion que simula el comportamiento del filosofo

    pthread_mutex_t *left_fork; //tenedor de la izquierda
    pthread_mutex_t *right_fork; //tenedor de la derecha

    long            last_meal; //tiempo de la utlima comida, se usa para detectar la muerte
    int             meals_eaten; //nº de comidas que ha realizado el filosofo

    t_data          *data; //puntero a la estructura compartida de la mesa, para acceder a los parametros globales y a los tenedores
}   t_philo;

/* ================= FUNCTIONS ================= */

/* init(reservar memoria, mutex...) */
int     parse_args(t_data *data, int ac, char **av);
int     init_data(t_data *data); //prepara la mesa antes de sentar a los filosofos
int     init_philos(t_data *data, t_philo **philos);

/* threads*/
void    start_threads(t_data *data, t_philo *philos);
void    *philo_routine(void *arg);

/* utils */
long    get_time(void); //devuelve el tiempo actual en milisegundos desde el inicio de la simulacion, se usa para calcular el tiempo transcurrido y para detectar la muerte de los filosofos
void    smart_sleep(long time); 
void    print_status(t_philo *philo, char *msg); //usa print_mutex para imprimir el estado del filosofo de forma sincronizada

/* cleanup */
void    destroy_all(t_data *data, t_philo *philos);
#endif