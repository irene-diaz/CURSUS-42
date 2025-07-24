/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:25:24 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 10:25:25 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
//CUADRADO
void	draw_square(t_data *img, int x0, int y0, int size, int color)
{
	for (int y = y0; y < y0 + size; y++)
		for (int x = x0; x < x0 + size; x++)
			my_mlx_pixel_put(img, x, y, color);
}

//CIRCULO
void	draw_circle(t_data *img, int cx, int cy, int radius, int color)
{
	int	dx;
	int	dy;

	for (int y = cy - radius; y <= cy + radius; y++)
	{
		for (int x = cx - radius; x <= cx + radius; x++)
		{
			dx = x - cx;
			dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
				my_mlx_pixel_put(img, x, y, color);
		}
	}
}

//TRIANGULO
void	draw_triangle(t_data *img, int x0, int y0, int height, int color)
{
	int	start;
	int	end;

	for (int y = 0; y < height; y++)
	{
		start = x0 - y;
		end = x0 + y;
		for (int x = start; x <= end; x++)
			my_mlx_pixel_put(img, x, y0 + y, color);
	}
}
//HEXAGONO
void	draw_hexagon(t_data *img, int cx, int cy, int size, int color)
{
	int	dx;

	for (int y = -size; y <= size; y++)
	{
		dx = size - abs(y);
		for (int x = -dx; x <= dx; x++)
			my_mlx_pixel_put(img, cx + x, cy + y, color);
	}
}

//DEGRADADOS
int	interpolate_color(int start, int end, float t)
{
	int	r;
	int	g;
	int	b;

	r = ((start >> 16) & 0xFF) + t * (((end >> 16) & 0xFF)
			- ((start >> 16) & 0xFF));
	g = ((start >> 8) & 0xFF) + t * (((end >> 8) & 0xFF)
			- ((start >> 8) & 0xFF));
	b = (start & 0xFF) + t * ((end & 0xFF) - (start & 0xFF));
	return (r << 16 | g << 8 | b);
}
//ARCOIRIS
void	draw_rainbow(t_data *img, int width, int height)
{
	int		num_colors;
	int		band_width;
	int		i;
	float	t;
	int		color;

	int colors[] = {
		0xFF0000, // rojo
		0xFF7F00, // naranja
		0xFFFF00, // amarillo
		0x00FF00, // verde
		0x0000FF, // azul
		0x4B0082, // índigo
		0x8B00FF  // violeta
	};
	num_colors = sizeof(colors) / sizeof(int);
	band_width = width / (num_colors - 1);
	for (int x = 0; x < width; x++)
	{
		// Calcular a qué franja pertenece
		i = x / band_width;
		if (i >= num_colors - 1)
			i = num_colors - 2;
		t = (float)(x % band_width) / band_width;
		color = interpolate_color(colors[i], colors[i + 1], t);
		for (int y = 0; y < height; y++)
			my_mlx_pixel_put(img, x, y, color);
	}
}
//TEXTURAS
void	draw_wave_texture(t_data *img, int width, int height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int offset = (int)(sin(x * 0.05) * 20); // onda vertical
			if (y == height / 2 + offset)
				my_mlx_pixel_put(img, x, y, 0x00FF00); // verde
		}
	}
}
*/
#include "ft_printf.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Uso: %s <mapa.ber>\n", argv[0]), 1);
	if (!init_game(argv[1], &game))
		return (1);
	if (!init_window(&game))
		return (1);
	load_images(&game);
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

/*int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;

	if (argc != 2)
	{
		printf("Uso: %s <mapa.ber>\n", argv[0]);
		return (1);
	}
	// Inicializa la conexión con el sistema gráfico
	mlx = mlx_init();
	// Crea una ventana 1920x1080
	mlx_win = mlx_new_window(mlx, 1000, 800, "so_long!");
	// Crea una imagen de 1920x1080
	img.img = mlx_new_image(mlx, 1000, 800);
	// Obtiene los datos internos de la imagen
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	// Pinta un solo píxel rojo en (5,5)
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			if (y % 10 != 0)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF0000);
			}
			else
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
			}
		}
	}*/
// aplicar degradado
/*for (int x = 0; x < 1000; x++)
{
	float t = (float)x / 800.0; // de 0.0 a 1.0
	color = interpolate_color(0x000000, 0xFFFFFF, t);
	for (int y = 0; y < 800; y++)
		my_mlx_pixel_put(&img, x, y, color);
}
//aplicar arcoiris
//draw_rainbow(&img, 1000, 800);
//my_mlx_pixel_put(&img, 3, 3, 0x00FF0000);

draw_wave_texture(&img, 10000, 800);
draw_square(&img, 50, 50, 100, 0x00FF0000);     // Cuadrado rojo
draw_circle(&img, 300, 100, 50, 0x0000FF00);     // Círculo verde
draw_triangle(&img, 500, 50, 60, 0x000000FF);    // Triángulo azul
draw_hexagon(&img, 700, 100, 40, 0x00FFFF00);    // Hexágono amarillo
// Coloca la imagen en la ventana
mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

// Inicia el bucle de eventos
mlx_loop(mlx);

return (0);
}*/

/*LEYENDA DEL MAPA
1 → muro

0 → suelo

P → jugador

C → coleccionable

E → salida*/