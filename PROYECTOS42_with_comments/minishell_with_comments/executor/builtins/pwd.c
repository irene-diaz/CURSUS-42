/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:02 by oem               #+#    #+#             */
/*   Updated: 2026/03/09 17:53:51 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== PWD ==================== */

/* Ejecuta el comando pwd(imprime el directorio actual) */
void	exec_pwd(t_cmd *cmd)
{
	char	cwd[1024];

	// Buffer donde getcwd almacenará el directorio actual. 1024 suele ser suficiente
	// pero podría quedarse corto en rutas muy largas; en ese caso getcwd devolvería NULL
	// getcwd devuelve un puntero al buffer si tiene éxito,o NULL en caso de error
	if (getcwd(cwd, sizeof(cwd)))
	{
		// Imprimir el directorio actual seguido de un salto de línea
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		// Si se proporcionó un puntero para exitcode, indicamos éxito (0)
		if (cmd->exitcode)
			*cmd->exitcode = 0;
	}
	/* En caso de error (por ejemplo buffer insuficiente o fallo del sistema),
	no imprimimos el directorio y si hay puntero,devolvemos código de error 1*/
	else if (cmd->exitcode)
		*cmd->exitcode = 1;
}
