/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:55:32 by abrecio-          #+#    #+#             */
/*   Updated: 2025/08/31 14:33:48 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_fd(int fd, char *stock)
{
	char	*buf;
	int		bytes_readed;
	char	*temp;

	bytes_readed = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (bytes_readed > 0 && (!ft_strchr(stock, '\n')))
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		if (bytes_readed < 0)
		{
			free(stock);
			free(buf);
			return (NULL);
		}
		buf[bytes_readed] = '\0';
		temp = stock;
		stock = ft_strjoin(stock, buf);
		free(temp);
	}
	free(buf);
	return (stock);
}

char	*extract_line(char *stock)
{
	int		i;
	char	*string;

	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	string = ft_substr(stock, 0, i + 1);
	return (string);
}

char	*updapte(char *stock)
{
	char	*temp;

	temp = stock;
	while (*stock != '\n' && *stock)
		stock++;
	if (*stock == '\n')
		stock++;
	if (*stock != '\0')
		stock = ft_strdup(stock);
	else
		stock = NULL;
	free(temp);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[2048];
	char		*string;

	string = NULL;
	if (fd < 0 || fd > 100)
		return (NULL);
	if (!stock[fd])
		stock[fd] = ft_strdup("");
	stock[fd] = read_fd(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	if (ft_strlen(stock[fd]) == 0)
	{
		free(stock[fd]);
		stock[fd] = NULL;
		return (NULL);
	}
	string = extract_line(stock[fd]);
	stock[fd] = updapte(stock[fd]);
	return (string);
}
