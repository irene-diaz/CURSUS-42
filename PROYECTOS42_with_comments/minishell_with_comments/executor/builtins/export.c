/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:53 by oem               #+#    #+#             */
/*   Updated: 2026/01/22 11:56:54 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXPORT ==================== */
static void	env_add(char ***envp, char *entry)
{
	int		i;
	char	**new_env;

	i = 0;
	// actualizar si ya existe
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], entry, ft_strchr(entry, '=') - entry)
			&& (*envp)[i][ft_strchr(entry, '=') - entry] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(entry);
			return ;
		}
		i++;
	}
	// añadir al final
	i = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i] = ft_strdup(entry);
	new_env[i + 1] = NULL;
	*envp = new_env;
}

void	exec_export(t_cmd *cmd)
{
	int i;
	char *equal;

	i = 1;
	while (cmd->cmd[i])
	{
		equal = ft_strchr(cmd->cmd[i], '=');
		if (equal)
			env_add(cmd->env_ptr, cmd->cmd[i]);
		i++;
	}
	if (cmd->exitcode)
		*cmd->exitcode = 0;
}