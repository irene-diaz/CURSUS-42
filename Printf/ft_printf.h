/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:55:11 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/08 18:02:57 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
int		ft_printf(const char *formato, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int nb);
size_t	ft_strlen(const char *str);
int		ft_putnbu(unsigned int nb);
int		ft_puthexa(size_t nb, char format);
int		ft_putp(void *ptr);
#endif