/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:14:33 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 17:48:16 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_player(char *line, t_game *game, int row)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'P')
		{
			if (game->player_x != -1)
			{
				ft_printf("Error: múltiples jugadores\n");
				return (0);
			}
			game->player_x = x;
			game->player_y = row;
			line[x] = '0';
		}
		if (line[x] == 'C')
			game->collectibles++;
		x++;
	}
	return (1);
}

int	read_and_parse(int fd, char **map, t_game *g, int *line_len)
{
	char	*line;
	int		i;

	i = 0;
	line = read_line_trimmed(fd);
	while (line)
	{
		if (!check_line_length(line, line_len))
		{
			free(line);
			free_partial_map(map, i);
			return (0);
		}
		if (!handle_player(line, g, i))
		{
			free(line);
			free_partial_map(map, i);
			return (0);
		}
		map[i++] = line;
		line = read_line_trimmed(fd);
	}
	map[i] = NULL;
	return (1);
}

char	**read_map(char *file, t_game *g)
{
	char	**map;
	int		fd;
	int		lines;
	int		len;

	len = -1;
	g->player_x = -1;
	g->player_y = -1;
	g->collectibles = 0;
	lines = count_lines(file);
	if (lines <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	if (!read_and_parse(fd, map, g, &len))
		return (close(fd), NULL);
	close(fd);
	return (map);
}
