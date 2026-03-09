/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:56:53 by oem               #+#    #+#             */
/*   Updated: 2026/03/09 17:51:34 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== EXPORT ==================== */

/* Añade una nueva variable de entorno */
static void	add_env(char ***envp, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	// Calcula el número de variables de entorno existentes
	while ((*envp)[i])
		i++;
	// Crea un nuevo array de punteros a char con espacio para la nueva variable y el NULL final
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	// Copia las variables de entorno existentes al nuevo array
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	// Añade la nueva variable al final del nuevo array
	new_env[i] = new_entry;
	// Añade un NULL al final del nuevo array para marcar el final de las variables de entorno
	new_env[i + 1] = NULL;
	// Libera la memoria del array de variables de entorno antiguo y actualiza el puntero para que apunte al nuevo array
	// free(*envp);
	*envp = new_env;
}

/* Actualiza o añade una variable de entorno */
static void	update_env(t_cmd *cmd, char *entry)
{
	int	i;
	int	len;

	len = 0;
	// Calcula la longitud del nombre de la variable (hasta el '=' o el final de la cadena)
	while (entry[len] && entry[len] != '=')
		len++;
	i = 0;
	// Recorre las variables de entorno para encontrar una coincidencia con el nombre de la variable
	while ((*cmd->env_ptr)[i])
	{
		// Compara el nombre de la variable con la entrada actual y verifica que el siguiente carácter sea '=' para asegurar una coincidencia exacta
		if (!ft_strncmp((*cmd->env_ptr)[i], entry, len)
			&& (*cmd->env_ptr)[i][len] == '=')
		{
			/* Si se encuentra una coincidencia,
				se libera la memoria de la variable de entorno existente y se asigna la nueva entrada */
			free((*cmd->env_ptr)[i]);
			(*cmd->env_ptr)[i] = ft_strdup(entry);
			return ;
		}
		i++;
	}
	/* Si no se encuentra una coincidencia,
		se añade la nueva variable de entorno al final de la lista */
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
		// Si el identificador es válido se actualiza o añade la variable de entorno
		update_env(cmd, entry);
		i++;
	}
	// Se establece el código de salida en 0
	*cmd->exitcode = 0;
}
