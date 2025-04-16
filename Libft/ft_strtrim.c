/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:46:09 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/16 17:08:44 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*result;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = 0;
	while (s1[end])
		end++;
	if (end > 0)
		end--;
	while (s1[start] && in_set(s1[start], set))
		start++;
	while (end > start && in_set(s1[end], set))
		end--;
	result = malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
