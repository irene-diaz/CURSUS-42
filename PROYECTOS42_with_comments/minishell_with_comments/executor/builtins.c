/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:22 by oem               #+#    #+#             */
/*   Updated: 2026/01/28 12:34:26 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== DISPATCHER ==================== */
int	exec_builtin(t_cmd *cmd)
{
	// Validar entrada: si no hay comando válido, no es un builtin
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	/*Comparar el nombre del comando con los builtins conocidos y llamar al
		manejador correspondiente. ft_strncmp se usa con el tamaño del string
	+1 para asegurar comparación exacta incluyendo el terminador.*/
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		exec_cd(cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		exec_exit(cmd);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		exec_pwd(cmd);
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		exec_echo(cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		exec_export(cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		exec_unset(cmd);
	else
		// Si no coincide con ningún builtin,indicar al llamador que no se ejecutó
		return (0);
	// Si llegamos aquí, se ejecutó un builtin: devolver 1
	return (1);
}
