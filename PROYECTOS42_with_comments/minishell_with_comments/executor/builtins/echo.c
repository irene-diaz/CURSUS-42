/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:37 by oem               #+#    #+#             */
/*   Updated: 2026/03/06 17:42:11 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== ECHO ==================== */

/* Verifica si la bandera -n está presente */
static int	is_n_flag(char *s)
{
	int	i;

	i = 1;
	// Verifica si la cadena comienza con '-'
	if (!s || s[0] != '-')
		return (0);
	// Verifica si la cadena está compuesta solo por 'n'
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* Maneja el código de salida de echo */
static int	handle_echo_exitcode(t_cmd *cmd)
{
	// Si no hay argumentos, no hay código de salida que manejar
	if (!cmd->cmd[1])
		return (0);
	// Verifica si el argumento es "$?"
	if (ft_strncmp(cmd->cmd[1], "$?", 2) == 0)
	{
		// Si el argumento es "$?", se imprime el código de salida
		if (cmd->exitcode)
			printf("%d\n", *cmd->exitcode);
		// Si no hay código de salida, se imprime 0
		else
			printf("0\n");
		// Se establece el código de salida a 0
		if (cmd->exitcode)
			*cmd->exitcode = 0;
		// Si no hay más argumentos, se devuelve 1
		if (!cmd->cmd[2])
			return (1);
	}
	return (0);
}

/* Imprime los argumentos de echo */
static void	print_echo_arguments(t_cmd *cmd, int i, int newline)
{
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1); // Imprime el argumento
		// Imprime un espacio entre argumentos
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	// Imprime una nueva línea si se requiere
	if (newline)
		ft_putstr_fd("\n", 1);
	// Restablece el código de salida
	if (cmd->exitcode)
		*cmd->exitcode = 0;
}

/* Ejecuta el comando echo */
void	exec_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	// Maneja el código de salida de echo
	if (handle_echo_exitcode(cmd))
		return ;
	// Verifica si se debe imprimir una nueva línea
	while (cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
	{
		newline = 0;
		i++;
	}
	// Imprime los argumentos de echo
	print_echo_arguments(cmd, i, newline);
}
