/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:32:52 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/01/28 13:35:02 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ejecutar una lista de comandos, manejando pipes y redirecciones
int	execute_cmd_list(t_cmd *cmd)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	char	*path;

	/*
		prev_fd: descriptor de lectura del pipe anterior. Si no hay pipe anterior
		su valor es
			-1. Se utiliza para encadenar pipelines: el stdout del proceso
		anterior se conecta al stdin del actual a través de prev_fd.
	*/
	prev_fd = -1;
	// Iterar sobre la lista de comandos (soporta pipelines con cmd->next)
	while (cmd)
	{
		// Si existe un siguiente comando, crear un pipe para conectar procesos.
		// fd[0] = extremo de lectura, fd[1] = extremo de escritura.
		if (cmd->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == 0)
		{
			/*
				Código que ejecuta el proceso hijo:
				- Restaurar señales a su comportamiento por defecto (set_signals_child)
				para que Ctrl-C/Ctrl-\ afecten al proceso hijo como a cualquier programa.
				- Configurar redirecciones de entrada/salida según prioridad:
					STDIN: cmd->infile > prev_fd (pipe previo) > STDIN_FILENO
					STDOUT: cmd->outfile > fd[1] (si hay siguiente comando) > STDOUT_FILENO
				- Cerrar descriptores que ya no se necesiten en el hijo para evitar
				fugas y que los pipes no queden abiertos impidiendo EOF.
				- Ejecutar builtins permitidos en hijo, o resolver y ejecutar un
				programa externo con execve.
			*/
			set_signals_child();
			/* STDIN: si el comando tiene redirección de entrada, usarla. Si no,
				y
				existe un pipe previo, conectar prev_fd a STDIN. */
			if (cmd->infile != STDIN_FILENO)
				dup2(cmd->infile, STDIN_FILENO);
			else if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			/* STDOUT: si el comando tiene redirección de salida, usarla. Si no,
				y
				hay un siguiente comando,
					conectar el extremo de escritura del pipe. */
			if (cmd->outfile != STDOUT_FILENO)
				dup2(cmd->outfile, STDOUT_FILENO);
			else if (cmd->next)
				dup2(fd[1], STDOUT_FILENO);
			/* Cerrar descriptores que ya no son necesarios en el hijo. Importante:
				tras dup2, los originales deben cerrarse. Además,
					si el hijo creó
				o heredó ambos extremos del pipe,
					cerrarlos para que el lector reciba EOF. */
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			/* Ejecutar builtins que estén permitidos dentro de un hijo.
				exec_builtin devuelve 1 si ejecutó un builtin; en ese caso el
				hijo termina con el código almacenado en cmd->exitcode. */
			if (exec_builtin(cmd))
				exit(*cmd->exitcode);
			// Resolver la ruta del ejecutable usando PATH o ruta con '/'
			path = resolve_path(cmd->arena, cmd->cmd[0], *(cmd->env_ptr));
			if (!path)
			{
				// Convención: 127 para "command not found". Mensaje por stderr.
				ft_putstr_fd("minishell: command not found\n", 2);
				exit(127);
			}
			// Reemplazar imagen del proceso con el ejecutable encontrado. Si
			// execve falla, imprimir perror y salir con 1.
			execve(path, cmd->cmd, *(cmd->env_ptr));
			perror("execve");
			exit(1);
		}
		/* PADRE: cerrar descriptores que ya no le hacen falta y preparar
			prev_fd para el siguiente comando de la pipeline. */
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			// El padre cierra el extremo de escritura del pipe (ya lo usará el hijo)
			close(fd[1]);
			// Guardar el extremo de lectura para conectarlo como stdin del siguiente hijo
			prev_fd = fd[0];
		}
		// Avanzar al siguiente comando de la lista
		cmd = cmd->next;
	}
	/* Esperar a que todos los procesos hijos terminen. El bucle espera
		hijos hasta que wait() devuelve <= 0. En un entorno real se
		podría usar waitpid para manejar señales intermedias o recuperar códigos
		individuales, pero aquí se espera a que terminen todos. */
	while (wait(&status) > 0)
		;
	return (0);
}
