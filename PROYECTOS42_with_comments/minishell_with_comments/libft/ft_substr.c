/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:54:47 by abrecio-          #+#    #+#             */
/*   Updated: 2025/04/24 16:54:49 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_empty(void)
{
	char	*s;

	s = malloc(1);
	if (s)
		s[0] = '\0';
	return (s);
}

static size_t	get_len(size_t s_len, unsigned int start, size_t len)
{
	if (start >= s_len)
		return (0);
	if (len > s_len - start)
		return (s_len - start);
	return (len);
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
	real_len = get_len(s_len, start, len);
	if (real_len == 0)
		return (alloc_empty());
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
