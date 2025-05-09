/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:33:51 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/09 13:45:00 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char	*p;
	char	*x;

	p = "Hola mundo";
	x = NULL;
	//!PRUEBA BASICA
	ft_printf("Hola %s, tienes %d años y tu inicial es %c.\n", "Ana", 25, 'A');
	//!PRUEBAS CON PUNTEROS
	ft_printf("%i",ft_printf("%p", x)); //DEVUELVE (nil) Y 5
	ft_printf("\n");
	ft_printf("Direccion de memoria: %p", p);
	ft_printf("\n");
	//!PRUEBA PASANDOLE NULO (no debe devolver nada)
	ft_printf("%i",ft_printf(NULL));
	//ft_printf("%");
	ft_printf("\n");
	//!PREBA NO PASANDOLE UN STRING(debe devolver (null) y 6)
	ft_printf("%i",ft_printf("%s", '\0'));
	ft_printf("\n");
	//!PRUEBA CON EL MINIMO INT(ddebe devolver el numero y 11)
	ft_printf("%i \n",ft_printf("%d", -2147483648));
}
