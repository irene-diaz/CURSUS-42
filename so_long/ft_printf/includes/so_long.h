/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:53:39 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:32:01 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		tile_size;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;

	// Imagenes
	void	*img_background;
	void	*img_player;
	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_collect;
}			t_game;

char		**read_map(char *file, t_game *game);
void		load_images(t_game *game);
void		draw_map(t_game *game);
// void    draw_background(t_game *game);
int			close_game(t_game *game);
int			handle_keypress(int keycode, t_game *game);
void		try_move_player(t_game *game, int dx, int dy);
void		move_up(t_game *game);
void		move_down(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);

void		free_map(char **map);
void		free_partial_map(char **map, int lines);
int			count_lines(char *file);
char		*read_line_trimmed(int fd);
int			check_line_length(char *line, int *len);

// FUNCIONES DE VALIDATE
int			validate_map(char **map, t_game *game);
int			is_rectangular(char **map);
int			check_top_bottom_walls(char **map, int width, int height);
int			check_side_walls(char **map, int width, int height);
int			is_surrounded_by_walls(char **map);

// FUNCIONES DE INIT_GAME
int			init_game(char *file, t_game *game);
int			init_window(t_game *game);

// Agrega más funciones y estructuras más adelante

#endif