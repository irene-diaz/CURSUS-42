/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:37:35 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/09 15:33:39 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		count += 5;
		return (ft_putstr("(nil)"));
	}
	count += ft_putstr("0x");
	count += ft_puthexa((size_t)ptr, 'x');
	return (count);
}
