/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:35:46 by oem               #+#    #+#             */
/*   Updated: 2025/07/23 18:35:49 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
{
	int	i;
	int	len;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_top_bottom_walls(char **map, int width, int height)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	check_side_walls(char **map, int width, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded_by_walls(char **map)
{
	int	width;
	int	height;

	if (!map || !map[0])
		return (0);
	width = ft_strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	if (!check_top_bottom_walls(map, width, height))
		return (0);
	if (!check_side_walls(map, width, height))
		return (0);
	return (1);
}
