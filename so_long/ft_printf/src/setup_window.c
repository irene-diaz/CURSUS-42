/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:26:57 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:27:39 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error al inicializar MiniLibX\n");
		free_map(game->map);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "so_long");
	if (!game->win)
	{
		ft_printf("Error al crear ventana\n");
		free_map(game->map);
		return (0);
	}
	return (1);
}
