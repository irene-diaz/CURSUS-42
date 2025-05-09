/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:11:32 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/09 13:45:50 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ifs(const char *formato, va_list *args)
{
	int	count;

	count = 0;
	if (*formato == 'd' || *formato == 'i')
		count += ft_putnbr(va_arg(*args, int));
	else if (*formato == 'c')
		count += ft_putchar(va_arg(*args, int));
	else if (*formato == 's')
		count += ft_putstr(va_arg(*args, char *));
	else if (*formato == 'u')
		count += ft_putnbu(va_arg(*args, unsigned int));
	else if (*formato == 'x' || *formato == 'X')
		count += ft_puthexa(va_arg(*args, unsigned int), *formato);
	else if (*formato == 'p')
		count += ft_putp(va_arg(*args, void *));
	else
		count += ft_putchar(*formato);
	return (count);
}

int	ft_printf(const char *formato, ...)
{
	va_list	args;
	int		count;

	if (!formato)
	{
		return (-1);
	}
	count = 0;
	va_start(args, formato);
	while (*formato)
	{
		if (*formato == '%')
		{
			formato++;
			count += ft_ifs(formato, &args);
		}
		else
		{
			count += ft_putchar(*formato);
		}
		formato++;
		va_end(args);
	}
	return (count);
}
