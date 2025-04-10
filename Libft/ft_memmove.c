/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:57:58 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/09 16:05:20 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d;
	const unsigned char *s;

	if (!dst && !src)
		return (NULL);

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;

	if (d < s)
	{
		for (size_t i = 0; i < len; i++)
			d[i] = s[i];
	}
	else
	{
		while (len--)
			d[len] = s[len];
	}
	return (dst);
}