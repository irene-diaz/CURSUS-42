/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:18:25 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 12:00:26 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*1. Si hay mas de 1 argumento, saca un error
  2. Parsea los argumentos
  3. Muestra error si no existe la estructura
  4. Sino esta ordenado, aplicamos push swap para ordenarlo(ksort o sort_small)
  5. Libera la memoria(para que no haya leaks)*/
int	main(int argc, char **argv)
{
	t_node	*a;

	if (argc < 2)
		return (0);
	a = parse_args(argc, argv);
	if (!a)
		error_and_exit();
	if (!is_sorted(a))
		push_swap(&a);
	free_stack(&a);
	return (0);
}
