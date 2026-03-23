/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:39:14 by abrecio-          #+#    #+#             */
/*   Updated: 2026/03/11 17:39:15 by abrecio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_arena.h"

static int	ft_len(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n)
	{
		++count;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa_arena(t_arena *arena, int n)
{
	char	*ptr;
	int		len;

	len = ft_len(n);
	ptr = arena_alloc(arena, len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	if (n == 0)
		ptr[0] = '0';
	else if (n < 0)
		ptr[0] = '-';
	while (n)
	{
		if (n < 0)
			ptr[--len] = -(n % 10) + '0';
		else
			ptr[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}
