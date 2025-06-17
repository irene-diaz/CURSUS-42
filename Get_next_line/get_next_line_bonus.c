/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:22:48 by oem               #+#    #+#             */
/*   Updated: 2025/06/05 11:16:18 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *stash)
{
	char	*buf;
	char	*temp;
	ssize_t	bytes;

	if (!stash)
		stash = ft_strdup("");
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(stash), NULL);
		buf[bytes] = '\0';
		temp = ft_strjoin(stash, buf);
		free(stash);
		stash = temp;
	}
	free(buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	len;
	char	*line;

	len = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		line = ft_substr(stash, 0, len + 1);
	else
		line = ft_substr(stash, 0, len);
	return (line);
}

static char	*trim_stash(char *stash)
{
	size_t	start;
	char	*new_stash;

	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, start + 1, ft_strlen(stash) - start - 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stashes[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	stashes[fd] = read_line(fd, stashes[fd]);
	if (!stashes[fd])
		return (NULL);
	line = extract_line(stashes[fd]);
	stashes[fd] = trim_stash(stashes[fd]);
	return (line);
}
