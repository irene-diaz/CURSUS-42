/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:22:09 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/12 13:31:27 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

//#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

/*int	main(void)
{
	unsigned int len = 3;
	char str[] = "abz";
	char str2[] = "aba";
	int n= ft_strncmp(str, str2, len);
	int n2 = strncmp(str, str2, len);

	printf("%i\n", n);
	printf("%i\n", n2);

}*/
