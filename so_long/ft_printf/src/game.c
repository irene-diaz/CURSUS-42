/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:43:18 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:44:58 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Funcion para cerrar el juego
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

static int	handle_tile(t_game *game, char tile, int new_x, int new_y)
{
	if (tile == '1')
		return (0);
	if (tile == 'C')
	{
		game->collectibles--;
		game->map[new_y][new_x] = '0';
	}
	if (tile == 'E')
	{
		if (game->collectibles == 0)
		{
			printf("¡Ganaste en %d movimientos!\n", ++game->moves);
			close_game(game);
			return (0);
		}
		return (0);
	}
	return (1);
}

// funcion que gestiona la logica del movimiento
void	try_move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	tile = game->map[new_y][new_x];
	if (!handle_tile(game, tile, new_x, new_y))
		return ;
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	printf("Movimientos: %d\n", game->moves);
	draw_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	else if (keycode == 'w' || keycode == 119 || keycode == 65362)
		move_up(game);
	else if (keycode == 's' || keycode == 115 || keycode == 65364)
		move_down(game);
	else if (keycode == 'a' || keycode == 97 || keycode == 65361)
		move_left(game);
	else if (keycode == 'd' || keycode == 100 || keycode == 65363)
		move_right(game);
	return (0);
}
