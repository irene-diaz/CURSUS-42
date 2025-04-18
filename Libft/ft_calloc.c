/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:58:06 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/16 13:35:20 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	nbytes;
	void	*ptr;

	nbytes = 1;
	if (nmemb == 0 || size == 0)
		ptr = malloc(1);
	else
	{
		nbytes = nmemb * size;
		if (nbytes / nmemb != size)
			return (NULL);
		ptr = malloc(nbytes);
	}
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nbytes);
	return (ptr);
}
