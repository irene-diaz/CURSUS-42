/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:36:30 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/09 13:17:55 by idiaz-ca         ###   ########.fr       */
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
		count += 6;
		return (ft_putstr("(null)"));
	}
	while (*str)
		count += ft_putchar(*str++);
	return (count);
}

int	ft_putnbr(long nb)
{
	int	count;

	count = 0;
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
