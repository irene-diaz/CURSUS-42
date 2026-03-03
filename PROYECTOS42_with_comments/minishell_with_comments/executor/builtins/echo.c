/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:37 by oem               #+#    #+#             */
/*   Updated: 2026/01/28 11:59:05 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== ECHO ==================== */

// Función auxiliar para comprobar si un argumento es la bandera -n
static int	is_n_flag(char *s)
{
	int	i;

	// Si s es NULL o no empieza por '-', no es la bandera -n
	i = 1;
	if (!s || s[0] != '-')
		return (0);
	// Comprobar que todos los caracteres después del '-' son 'n'
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Maneja el caso especial de "echo $?". Devuelve 1 si se imprimió y no debe continuar
static int	handle_echo_exitcode(t_cmd *cmd)
{
	// Si no hay primer argumento, no hacemos nada
	if (!cmd->cmd[1])
		return (0);
	// Si el primer argumento es "$?" imprimimos el código de salida almacenado
	if (ft_strncmp(cmd->cmd[1], "$?", 2) == 0)
	{
		if (cmd->exitcode)
			printf("%d\n", *cmd->exitcode);
		else
			printf("0\n");
		// Tras imprimir, fijamos el exitcode a 0 (operación exitosa)
		if (cmd->exitcode)
			*cmd->exitcode = 0;
		// Si solo se pasó "$?" (sin más argumentos),indicamos que no debe continuar
		if (!cmd->cmd[2])
			return (1);
	}
	return (0);
}

// Imprime los argumentos del comando echo desde la posición i
static void	print_echo_arguments(t_cmd *cmd, int i, int newline)
{
	// Imprime argumentos desde la posición i, separándolos por espacios
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	// Añade salto de línea si no se detectó la bandera -n
	if (newline)
		ft_putstr_fd("\n", 1);
	// Establece exitcode a 0 (éxito) si se proporcionó el puntero
	if (cmd->exitcode)
		*cmd->exitcode = 0;
}

// Implementación del comando echo
void	exec_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	// i comienza en 1 para saltar el nombre del comando
	i = 1;
	// Por defecto imprimimos salto de línea al final
	newline = 1;
	// Manejar posible impresión de "$?". Si handle_echo_exitcode devuelve 1,
	// significó que era el único argumento y ya imprimimos,por lo que terminamos.
	if (handle_echo_exitcode(cmd))
		return ;
	// Procesar banderas -n consecutivas (ej. -n -nn)
	while (cmd->cmd[i] && is_n_flag(cmd->cmd[i]))
	{
		newline = 0; // no imprimir salto de línea final
		i++;
	}
	// Imprimir los argumentos restantes a partir de i
	print_echo_arguments(cmd, i, newline);
}
