/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:42 by oem               #+#    #+#             */
/*   Updated: 2026/01/28 12:20:42 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXIT ==================== */
void	exec_exit(t_cmd *cmd)
{
	int	status;

	// Valor por defecto del status es 0 (éxito)
	status = 0;
	// Si se proporciona un argumento,lo convertimos a entero y lo usamos como status
	// ft_atoi devuelve 0 si la cadena no es numérica,como en muchas implementaciones
	if (cmd->cmd[1])
		status = ft_atoi(cmd->cmd[1]);
	// Si se proporcionó un puntero para almacenar el exitcode, lo actualizamos
	if (cmd->exitcode)
		*cmd->exitcode = status;
	// Limpiar el historial de readline antes de terminar para liberar recursos
	rl_clear_history();
	// Terminar el proceso con el código de salida solicitado
	exit(status);
}
