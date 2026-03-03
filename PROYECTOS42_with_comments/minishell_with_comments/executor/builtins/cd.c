/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:32 by oem               #+#    #+#             */
/*   Updated: 2026/01/28 11:36:59 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== CD ==================== */
void	exec_cd(t_cmd *cmd)
{
	int	ret;

	// Variable para almacenar el valor devuelto por chdir:
	// chdir devuelve 0 si cambia el directorio con éxito, y -1 en caso de error
	// Si no se proporciona un argumento (solo "cd"), intentamos ir al HOME
	// getenv("HOME") puede devolver NULL si la variable no está definida
	if (!cmd->cmd[1])
		ret = chdir(getenv("HOME"));
	else
		// Si hay argumento, intentamos cambiar al directorio indicado
		ret = chdir(cmd->cmd[1]);
	// Si chdir devolvió un valor distinto de 0 hubo un error
	if (ret != 0)
	{
		// perror imprime un mensaje de error en stderr con el prefijo dado
		perror("minishell: cd");
		// Si se pasó un puntero para el código de salida, lo ajustamos a 1 (error)
		if (cmd->exitcode)
			*cmd->exitcode = 1;
	}
	else if (cmd->exitcode)
		// Si chdir fue exitoso, fijamos el código de salida a 0
		*cmd->exitcode = 0;
}
