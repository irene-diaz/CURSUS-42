/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_short.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:54:29 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/25 14:35:45 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/*static char buffer[BUFFER_SIZE];
Memoria persistente entre llamadas. Guarda lo último leído del fichero.

static int	pos_read;
Índice actual dentro del buffer (cuántos caracteres ya hemos consumido).

static int	pos_b;
Número de bytes válidos en buffer tras el último read.

char		*line;
Donde vamos a ir construyendo la línea.

int			i;
Índice de escritura dentro de line.*/
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	static int	pos_read;
	static int	pos_b;
	int			i;

	// control de errores
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	// reserva de memoria
	line = malloc(10000);
	i = 0;
	while (1)
	{
		/*Si ya hemos consumido todo el buffer (pos_b <= pos_read),
			hacemos un nuevo read.*/
		if (pos_b <= pos_read)
		{
			// guardamos cuantos bytes se han leido
			pos_b = read(fd, buffer, BUFFER_SIZE);
			// reiniciamos el indice de lectura
			pos_read = 0;
			// si hay errores el read, salimos del bucle
			if (pos_b <= 0)
				break ;
		}
		// si hay datos en el buffer ,copiamos caracter a caracter dentro de la linea
		line[i++] = buffer[pos_read++];
		/*si encontramos un salto de linea,
			terminamos la linea y salimos del bucle*/
		if (line[i - 1] == '\n')
			break ;
	}
	// Terminanos la linea con el caracter final de linea
	line[i] = '\0';
	// Si no copiamos nada (i == 0), liberamos y devolvemos NULL (EOF).
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	// devolvemos la linea leida
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	// abrimos el archivo(en este caso en modo lectura)
	fd = open("file.txt", O_RDONLY);
	// llamamos a get_next_line en bucle para que nos vaya leyendo linea  a linea
	while ((line = get_next_line(fd)))
	{
		// mostramos cada linea
		printf("%s", line);
		// luego de mostrarla la liberamos
		free(line);
	}
	// cerramos el archivo
	close(fd);
	return (0);
}
