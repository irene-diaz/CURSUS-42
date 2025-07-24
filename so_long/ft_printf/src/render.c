/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:35:23 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:40:03 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Fondo completo (wallpaper)
	game->img_background = mlx_xpm_file_to_image(game->mlx,
			"textures/background.xpm", &w, &h);
			game->img_background = opcional*/

void	load_images(t_game *game)
{
	int	w;
	int	h;

	game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &w,
			&h);
	if (!game->img_floor)
	{
		ft_printf("Error: No se pudo cargar floor.xpm\n");
		exit(1);
	}
	game->tile_size = w;
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &w,
			&h);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &w,
			&h);
	game->img_collect = mlx_xpm_file_to_image(game->mlx, "textures/collect.xpm",
			&w, &h);
	if (!game->img_floor || !game->img_wall || !game->img_player
		|| !game->img_exit || !game->img_collect)
	{
		ft_printf("Error: No se pudo cargar una o más texturas\n");
		exit(1);
	}
}
// cuánto mide cada celda del mapa (en píxeles) al renderizar con MiniLibX.

void	draw_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * game->tile_size, y
		* game->tile_size);
}

void	draw_map(t_game *game)
{
	char	tile;
	int		x;
	int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, game->img_floor, x, y);
			tile = game->map[y][x];
			if (tile == '1')
				draw_tile(game, game->img_wall, x, y);
			else if (tile == 'E')
				draw_tile(game, game->img_exit, x, y);
			else if (tile == 'C')
				draw_tile(game, game->img_collect, x, y);
			x++;
		}
		y++;
	}
	draw_tile(game, game->img_player, game->player_x, game->player_y);
}
