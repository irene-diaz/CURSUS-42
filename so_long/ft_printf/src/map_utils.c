/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:28:38 by oem               #+#    #+#             */
/*   Updated: 2025/07/24 09:47:31 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	free_partial_map(char **map, int lines)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	c;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			count++;
	}
	close(fd);
	return (count + 1);
}

char	*read_line_trimmed(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	check_line_length(char *line, int *len)
{
	int	l;

	l = ft_strlen(line);
	if (*len == -1)
		*len = l;
	else if (l != *len)
		return (0);
	return (1);
}
