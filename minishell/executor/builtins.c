/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:21:55 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/09 18:00:11 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== DISPATCHER ==================== */

/* Execute the built-in commands */
int	exec_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
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
		return (0);
	return (1);
}
