/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:23:03 by oem               #+#    #+#             */
/*   Updated: 2025/06/04 09:01:24 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>  // open
#include <stdio.h>  // printf, perror
#include <stdlib.h> // free, exit

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Uso: %s <archivo>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir archivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINEA: %s", line);
		free(line);
	}
	close(fd);
	return (0);
}
