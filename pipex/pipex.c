/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:22:40 by oem               #+#    #+#             */
/*   Updated: 2025/08/11 13:45:22 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// FUNCION PARA LANZAR ERRORES
/* perror es una función de C que imprime un mensaje de error en la salida
		estándar de error (stderr),indicando la causa del error*/
/*EXIT_FAILURE(salimos del programa)*/
void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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
char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
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
			return (full_path);
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

/*FUNCION PARA EJECUTAR UN COMANDO DE SHELL
1. Dividir el comando en argumentos
2. Verificar que ft_split no haya fallado
3. Buscar el path absoluto del comando
4. Verificar si se encontro el binario (127= UNIX “command not found”)
5. Ejecutar el comando con execve(reemplaza el proceso actual con el cmd_path),
si funciona, no vuelve nunca más a la siguiente línea.
6. Si execve falla, mostrar el error
7. Limpiar memoria y salir (Libera los argumentos y la ruta del comando.)
*/

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		error_exit("split");
	cmd_path = get_cmd_path(args[0]);
	if (!cmd_path)
	{
		ft_free_split(args);
		ft_printf("pipex: command not found: %s\n", args[0]);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	ft_free_split(args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

/*Esta función representa el primer hijo (child1) del proceso pipex.
Su tarea es:

Leer desde archivo1 y escribir el resultado de comando1 al pipe,
	para que otro proceso lo pueda leer.

Equivale a esto en la shell: < archivo1 comando1 | */
/*1. Abrir el archivo de entrada (archivo1)
Abre archivo1 en modo lectura (O_RDONLY).
Si falla (no existe o no hay permisos), imprime el error y termina.
2. Redirigir STDIN(entrada estandar) al archivo
3. Redirigir STDOUT(salida estandar) al pipe
4. Cerrar descriptores que ya no se usan
5. Ejecutar el primer comando
*/
void	child1_process(char **argv, int *pipe_fd, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error_exit("open infile");
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(infile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(argv[2], envp);
}

/*Esta función representa el proceso que:

Lee la salida de comando1 desde el pipe, ejecuta comando2,
	y escribe su salida final en archivo2.

En la shell, es equivalente a esto: ... | comando2 > archivo2*/
/*1. Abrir el archivo de salida (archivo2)
Si falla (por permisos, disco lleno, etc.), se lanza un error.
2. Redirigir entrada estándar (STDIN) al pipe
3. Redirigir salida estándar (STDOUT) al archivo
4. Cerrar descriptores innecesarios
5. Ejecutar el segundo comando

*/
void	child2_process(char **argv, int *pipe_fd, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		error_exit("open outfile");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(argv[3], envp);
}
