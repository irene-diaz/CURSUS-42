/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:21:22 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/12 09:21:15 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXIT ==================== */
/* Handle the exit status for the shell */
void	exec_exit(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->cmd[1])
		status = ft_atoi(cmd->cmd[1]);
	if (cmd->exitcode)
		*cmd->exitcode = status;
	if (cmd->env_ptr && *cmd->env_ptr)
		free_env(*cmd->env_ptr);
	if (cmd->arena)
		arena_destroy(cmd->arena);
	rl_clear_history();
	exit(status);
}
