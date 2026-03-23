/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:34:07 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/03/10 13:57:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXPORT ==================== */

/* Add a new environment variable */
static void	add_env(char ***envp, char *new_entry)
{
	int		i;
	char	**new_env;
	char	**old_env;

	old_env = *envp;
	i = 0;
	while (old_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	*envp = new_env;
	free(old_env);
}

/* Update an existing environment variable */
static void	update_env(t_cmd *cmd, char *entry)
{
	int	i;
	int	len;

	len = 0;
	while (entry[len] && entry[len] != '=')
		len++;
	i = 0;
	while ((*cmd->env_ptr)[i])
	{
		if (!ft_strncmp((*cmd->env_ptr)[i], entry, len)
			&& (*cmd->env_ptr)[i][len] == '=')
		{
			free((*cmd->env_ptr)[i]);
			(*cmd->env_ptr)[i] = ft_strdup(entry);
			return ;
		}
		i++;
	}
	add_env(cmd->env_ptr, ft_strdup(entry));
}

/* Print all environment variables */
static void	print_env_variables(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[j], 1);
		ft_putstr_fd("\n", 1);
		j++;
	}
}

/* Execute the export command */
void	exec_export(t_cmd *cmd)
{
	int		i;
	char	*entry;

	i = 1;
	if (!cmd->cmd[1])
	{
		print_env_variables(*cmd->env_ptr);
		*cmd->exitcode = 0;
		return ;
	}
	while (cmd->cmd[i])
	{
		if (handle_invalid_identifier(cmd, cmd->cmd[i]))
			return ;
		if (ft_strchr(cmd->cmd[i], '='))
			entry = cmd->cmd[i];
		else
			entry = ft_strjoin(cmd->cmd[i], "=");
		update_env(cmd, entry);
		if (!ft_strchr(cmd->cmd[i], '='))
			free(entry);
		i++;
	}
	*cmd->exitcode = 0;
}
