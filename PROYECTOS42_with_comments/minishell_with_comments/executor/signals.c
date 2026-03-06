/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:32:15 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/06 17:28:21 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_signal = 0; // Variable global para almacenar señales
/*TEORIA
SIGINT

Señal generada por el terminal cuando el usuario pulsa Ctrl‑C.
Acción por defecto (SIG_DFL): terminar el proceso.
En un shell interactivo suele instalarse un manejador para no cerrar el propio shell sino solo
interrumpir la entrada actual.

SIGQUIT

Señal generada por Ctrl‑\.
Acción por defecto (SIG_DFL): terminar el proceso y producir un core dump (volcado de memoria) para
depuración.
Suele ignorarse (SIG_IGN) en el shell interactivo para evitar que el usuario consiga core dumps del
propio shell.

SIG_IGN

Valor especial que indica “ignorar la señal”.
Pasar SIG_IGN a signal() hace que la señal sea descartada: el proceso no recibe ni ejecuta acción
alguna.

SIG_DFL

Valor especial que restaura el comportamiento por defecto de la señal (terminar,
	detener, ignorar, según la señal).
Útil en procesos hijo antes de exec para que respondan a Ctrl‑C/Ctrl‑\ como cualquier programa normal.

Uso típico con signal():

	signal(SIGINT,handle_sigint) → instalar un handler personalizado.
	signal(SIGQUIT,SIG_IGN) → ignorar Ctrl‑.
	signal(SIGINT,SIG_DFL) → restaurar comportamiento por defecto.
*/

// Manejador para SIGINT (Ctrl-C) en el modo interactivo
// - Escribe un salto de línea para dejar la línea actual limpia
// - Notifica a readline que hay una nueva línea,reemplaza la línea actual
//   por una vacía y vuelve a mostrar el prompt
static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 130;         // Captura la señal SIGINT
	rl_on_new_line();       // preparar readline para una nueva línea
	rl_replace_line("", 0); // vaciar la línea actual introducida por el usuario
	rl_redisplay();         // volver a dibujar el prompt
}

// Configurar señales para el proceso interactivo (el shell)
// - SIGINT: usar handle_sigint para que Ctrl-C no cierre el shell sino que
//   interrumpa la entrada actual y devuelva el prompt
// - SIGQUIT: ignorarlo (Ctrl-\) para que no termine el shell
void	set_signals_interactive(void)
{
	signal(SIGINT, handle_sigint); // "Ctrl-C"
	signal(SIGQUIT, SIG_IGN);      // "Ctrl-\\"
}

// Configurar señales para procesos hijos (comandos ejecutados)
// - Restaurar el comportamiento por defecto para que las señales actúen
//   normalmente sobre los procesos hijos(en minishell no interactivo)
void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
