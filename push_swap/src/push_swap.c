/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:00:56 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 12:03:06 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Main Funcion que decide que algoritmo usar en funcion del nº de elementos
void	push_swap(t_node **a)
{
	t_node	*b;
	int		size;

	b = NULL;
	size = stack_size(*a);
	assign_indexes(*a);
	if (size <= 5)
		sort_small(a, &b);
	else
		ksort(a, &b);
}
