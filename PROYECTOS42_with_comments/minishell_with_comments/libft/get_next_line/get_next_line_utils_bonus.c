/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:55:41 by abrecio-          #+#    #+#             */
/*   Updated: 2025/08/30 18:55:58 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s || (char)c == '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	buffer;
	size_t	i;
	char	*ptr;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buffer = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(buffer);
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*(ptr + i++) = *s1++;
	while (*s2)
		*(ptr + i++) = *s2++;
	*(ptr + i) = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;
	size_t	real_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		real_len = s_len - start;
	else
		real_len = len;
	sub = malloc(real_len + 1);
	if (!sub)
		return (NULL);
	while (i < real_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
