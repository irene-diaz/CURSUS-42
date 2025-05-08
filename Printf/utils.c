/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:36:30 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/08 18:04:29 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (ft_putstr("(null)"));
	}
	while (*str)
		count += ft_putchar(*str++);
	return (count);
}

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
	}
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_putnbu(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
		count += ft_putnbu(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

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

int	ft_puthexa(size_t nb, char format)
{
	int		count;
	char	*dic;

	if (format == 'X')
		dic = "0123456789ABCDEF";
	else
	{
		dic = "0123456789abcdef";
	}
	count = 0;
	if (nb >= 16)
	{
		count += ft_puthexa(nb / 16, format);
	}
	count += ft_putchar(dic[nb % 16]);
	return (count);
}

int	ft_putp(void *ptr)
{
	int	count;

	count = 0;
	if (ptr == NULL)
	{
		return (ft_putstr("(nil)"));
	}
	count += ft_putstr("0x");
	count += ft_puthexa((size_t)ptr, 'x');
	return (count);
}
