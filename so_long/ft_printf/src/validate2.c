/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:36:44 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:12:55 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_required_elements(char **map, t_game *game)
{
	int	i;
	int	j;
	int	exit;

	i = -1;
	exit = 0;
	if (game->player_x == -1 || game->player_y == -1)
	{
		ft_printf("Error: No se encontró la posición del jugador (P)\n");
		return (0);
	}
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'E')
				exit++;
	}
	if (exit < 1 || game->collectibles < 1)
	{
		ft_printf("Error: Faltan E o C en el mapa\n");
		return (0);
	}
	return (1);
}

int	has_only_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'P'
				&& map[i][j] != 'E' && map[i][j] != 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(char **map, t_game *game)
{
	if (!map || !map[0])
		return (ft_printf("Error: El mapa está vacío o no se pudo cargar\n"),
			0);
	if (!is_rectangular(map))
		return (ft_printf("Error: El mapa no es rectangular\n"), 0);
	if (!is_surrounded_by_walls(map))
		return (ft_printf("Error: El mapa no está rodeado por muros\n"), 0);
	if (!has_required_elements(map, game))
		return (0);
	if (!has_only_valid_chars(map))
		return (ft_printf("Error: Caracteres inválidos en el mapa\n"), 0);
	return (1);
}
