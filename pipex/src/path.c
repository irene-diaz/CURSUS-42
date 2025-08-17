/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:20:26 by oem               #+#    #+#             */
/*   Updated: 2025/08/17 18:20:27 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
/* FUNCION PARA OBTENER LA RUTA ABSOLUTA DEL COMANDO QUE QUREMOS EJECUTAR
(como ls, wc, grep, etc.) USANDO LA VARUABLE DE ENTORNO PATH
1. Obtener la variable de entorno path(PATH contiene una lista de directorios
 separados por : donde el sistema busca los comandos.)
2. Verificar si PATH existe
3. Dividir PATH en rutas individuales(ademas comprobamos si existen)
4. Recorremos cada ruta y construimos el camino completo
	a-(Se usa ft_strjoin dos veces: una para agregar el / y otra para
	agregar el nombre del comando.)
	b-Verificar si ese path existe y es ejecutable(X_OK si tiene permisos x)
	c-Si no es válida, liberamos memoria y seguimos
5. Sino encontramos ninguna ruta valida liberamos todo */

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	path_env = ft_getenv("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
