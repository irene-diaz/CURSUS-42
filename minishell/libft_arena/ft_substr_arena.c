/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:39:46 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/11 17:39:47 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_arena.h"

static char	*alloc_empty_arena(t_arena *arena)
{
	char	*s;

	s = arena_alloc(arena, 1);
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

char	*ft_substr_arena(t_arena *arena, char const *s, unsigned int start,
		size_t len)
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
		return (alloc_empty_arena(arena));
	sub = arena_alloc(arena, real_len + 1);
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
