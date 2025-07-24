/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:45:31 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:47:15 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game)
{
	try_move_player(game, 0, -1);
}

void	move_down(t_game *game)
{
	try_move_player(game, 0, 1);
}

void	move_left(t_game *game)
{
	try_move_player(game, -1, 0);
}

void	move_right(t_game *game)
{
	try_move_player(game, 1, 0);
}
