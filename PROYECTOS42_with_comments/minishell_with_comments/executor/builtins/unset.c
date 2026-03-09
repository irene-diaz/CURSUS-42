/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:26 by oem               #+#    #+#             */
/*   Updated: 2026/03/09 17:59:28 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ==================== UNSET ==================== */

/* Cuenta el número de variables de entorno */
static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/* Copia las variables de entorno,
	omitiendo la variable que se quiere eliminar */
static void	copy_env_vars(char **old_env, char **new_env, char *key, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// Recorre las variables de entorno y copia todas excepto la que coincide con la clave a eliminar
	while (old_env[i])
	{
		if (!(ft_strncmp(old_env[i], key, len) == 0 && old_env[i][len] == '='))
			new_env[j++] = old_env[i];
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
}

/* Elimina una variable de entorno */
static void	remove_env(t_cmd *cmd, char *key)
{
	int		len;
	char	**old_env;
	char	**new_env;
	int		count;

	// obtiene el array de variables de entorno actual
	old_env = *cmd->env_ptr;
	// Calcula la longitud de la clave para comparar con las variables de entorno
	len = ft_strlen(key);
	// Cuenta el número de variables de entorno para asignar memoria al nuevo array
	count = count_env_vars(old_env);
	// Crea un nuevo array de punteros a char con espacio para las variables de entorno restantes y el NULL final
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return ;
	/* Copia las variables de entorno, omitiendo la que se quiere eliminar */
	copy_env_vars(old_env, new_env, key, len);
	free(old_env);
	// Actualiza el puntero de variables de entorno para que apunte al nuevo array
	*cmd->env_ptr = new_env;
}

/* Ejecuta el comando unset,
	eliminando las variables de entorno especificadas en los argumentos */
void	exec_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		remove_env(cmd, cmd->cmd[i]);
		i++;
	}
	*cmd->exitcode = 0;
}
