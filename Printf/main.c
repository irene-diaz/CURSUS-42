/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:33:51 by idiaz-ca          #+#    #+#             */
/*   Updated: 2025/05/08 18:04:17 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	char	*p;

	p = "Hola mundo";
	ft_printf("Hola %s, tienes %d años y tu inicial es %c.\n", "Ana", 25, 'A');
	ft_printf("Direccion de memoria: %p", p);
	// printf("Hola %s, tienes %d años y tu inicial es %c.\n", "Ana", 25, 'A');
}
