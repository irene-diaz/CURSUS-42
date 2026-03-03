/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:26 by oem               #+#    #+#             */
/*   Updated: 2026/01/22 11:57:27 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== UNSET ==================== */
void	exec_unset(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->cmd[i])
	{
		j = 0;
		while ((*cmd->env_ptr)[j])
		{
			if (!ft_strncmp((*cmd->env_ptr)[j], cmd->cmd[i],
					ft_strlen(cmd->cmd[i]))
				&& (*cmd->env_ptr)[j][ft_strlen(cmd->cmd[i])] == '=')
			{
				free((*cmd->env_ptr)[j]);
				while ((*cmd->env_ptr)[j])
				{
					(*cmd->env_ptr)[j] = (*cmd->env_ptr)[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	if (cmd->exitcode)
		*cmd->exitcode = 0;
}
