/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:35:56 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/11 02:03:08 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal = 0;

/* Handle SIGINT (Ctrl+C) */
static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* Set the signal handlers for the interactive shell */
void	set_signals_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/* Set the signal handlers for the child process */
void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
