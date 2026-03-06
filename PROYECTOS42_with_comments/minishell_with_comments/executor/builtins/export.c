/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:53 by oem               #+#    #+#             */
/*   Updated: 2026/03/06 17:56:49 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXPORT ==================== */

static void	add_env(char ***envp, char *new_entry)
{
	int		i;
	char	**new_env;

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
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	*envp = new_env;
}

static void	env_add(t_cmd *cmd, char *entry)
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

/* Imprime las variables de entorno */
static void	print_env_variables(char **envp)
{
	int	j;

	j = 0;
	/* Recorre las variables de entorno y las imprime en el formato "declare
		-x VAR=value"*/
	while (envp[j])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[j], 1);
		ft_putstr_fd("\n", 1);
		j++;
	}
}

/* Ejecuta el comando export */
void	exec_export(t_cmd *cmd)
{
	int	i;

	char *entry; // Variable para almacenar la entrada
	i = 1;
	// Si no hay argumentos, imprime las variables de entorno
	if (!cmd->cmd[1])
	{
		print_env_variables(*cmd->env_ptr);
		*cmd->exitcode = 0;
		return ;
	}
	// Si hay argumentos, los añade a las variables de entorno
	while (cmd->cmd[i])
	{
		// Si hay un identificador inválido
		if (handle_invalid_identifier(cmd, cmd->cmd[i]))
			return ;
		// si cmd->cmd[i] contiene un '=', se asigna a entry
		if (ft_strchr(cmd->cmd[i], '='))
			entry = cmd->cmd[i];
		// si cmd->cmd[i] no contiene un '=', se crea una nueva entrada
		else
			entry = ft_strjoin(cmd->cmd[i], "=");
		// Si el identificador es válido, se añade a las variables de entorno
		env_add(cmd, entry);
		i++;
	}
	// Se establece el código de salida en 0
	*cmd->exitcode = 0;
}
