/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:55:55 by oem               #+#    #+#             */
/*   Updated: 2026/01/28 13:00:39 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Obtener la variable de entorno PATH
static char	*get_path_env(char **envp)
{
	int	i;

	// Buscar la variable de entorno PATH en el array envp
	// Devuelve un puntero al contenido después de "PATH=" o NULL si no existe
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// Buscar el ejecutable en los directorios especificados en paths
static char	*find_executable_in_paths(t_arena *arena, char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	// Concatenar cada directorio de PATH con '/'+ cmd y comprobar si es ejecutable
	// Se usa el arena allocator para las cadenas temporales (ft_strjoin_arena)
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_arena(arena, paths[i], "/");
		full_path = ft_strjoin_arena(arena, full_path, cmd);
		// access(..., X_OK) devuelve 0 si el fichero es ejecutable
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	// No se encontró el ejecutable en los directorios de PATH
	return (NULL);
}

// Resolver la ruta completa del comando usando PATH
char	*resolve_path(t_arena *arena, char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	// Validación básica
	if (!cmd)
		return (NULL);
	/* Si el comando contiene una barra '/',se interpreta como ruta relativa
	En ese caso comprobamos directamente si es ejecutable*/
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	// Obtener la variable PATH del entorno
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	// Separar PATH por ':' obteniendo un array de directorios gestionado por el arena
	paths = ft_split_arena(path_env, ':', arena);
	if (!paths)
		return (NULL);
	// Buscar el ejecutable en los directorios resultantes
	return (find_executable_in_paths(arena, cmd, paths));
}
/*STDIN_FILENO = 0 → entrada estándar (teclado normalmente).
STDOUT_FILENO = 1 → salida estándar (pantalla normalmente).
(Relacionado) STDERR_FILENO = 2 → salida de error estándar.
Se definen en <unistd.h> y se usan con llamadas como read, write, dup2, close,
etc. Por ejemplo, dup2(fd,STDOUT_FILENO) hace que las salidas escritas en stdout
vayan ahora al descriptor fd.*/
// Aplicar las redirecciones de entrada/salida del comando
void	apply_redirections(t_cmd *cmd)
{
	// Si infile no es el descriptor estándar,duplicarlo a stdin y cerrar el original
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	// Si outfile no es el descriptor estándar,duplicarlo a stdout y cerrar el original
	if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
}
