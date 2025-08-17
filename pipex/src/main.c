/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:56:54 by oem               #+#    #+#             */
/*   Updated: 2025/08/11 13:43:45 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	1. Validar número de argumentos
	2. Crear el pipe
	3. Crear el primer hijo: ejecuta comando1
	4. Crear el segundo hijo: ejecuta comando2
	5. Cerrar ambos extremos del pipe en el proceso padre
	6. Esperar a los procesos hijos (con esto nos aseguramos que no se creen
	zoombie proceses y que el programa termine de forma ordenada)
*/
int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_printf("Uso: %s archivo1 comando1 comando2 archivo2\n", argv[0], 1);
	}
	if (pipe(pipe_fd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		child1_process(argv, pipe_fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
		child2_process(argv, pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
