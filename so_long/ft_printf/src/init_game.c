/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:25:57 by oem               #+#    #+#             */
/*   Updated: 2025/07/25 01:12:19 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

static int	validate_and_set_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		ft_printf("%s\n", game->map[i++]);
	if (!validate_map(game->map, game))
	{
		ft_printf("Mapa inválido\n");
		free_map(game->map);
		return (0);
	}
	game->tile_size = 100;
	game->height = 0;
	while (game->map[game->height])
		game->height++;
	game->width = ft_strlen(game->map[0]);
	return (1);
}

int	init_game(char *file, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->player_x = -1;
	game->player_y = -1;
	game->collectibles = 0;
	game->map = read_map(file, game);
	if (!game->map)
	{
		ft_printf("Error al leer el mapa\n");
		return (0);
	}
	if (!validate_and_set_map(game))
		return (0);
	return (1);
}
