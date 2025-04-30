/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:11:32 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/04/30 13:33:40 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>
#include <unistd.h>

/*printf devuelve la cantidad de caracteres que le pases*/

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
int	ft_printf(const char *format, ...)
{
	int		i;
	int		j;
	size_t	len;
	va_list	args;

	i = 0;
	j = 0;
	len = ft_strlen(argument_list);
	ft_putstr_fd(argument_list, 1);
	// write(1, &p, 1);
	return (len);
}
int	main(void)
{
	printf("%d", ft_printf("d", 1));
	printf("%d", printf("%d", 1));
}
