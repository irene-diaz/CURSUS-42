/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:39:02 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/11 17:39:03 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_arena.h"

void	*ft_calloc_arena(t_arena *arena, size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	ptr = arena_alloc(arena, total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', total);
	return (ptr);
}
