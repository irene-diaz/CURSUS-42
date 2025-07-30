/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_reverse_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:26:13 by oem               #+#    #+#             */
/*   Updated: 2025/07/28 14:34:13 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*Desplaza hacia abajo todos los elementos del stack a una
posición, de forma que el último elemento se convierte en el primero.*/
void	rra(t_node **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

/* Desplaza hacia abajo todos los elementos del stack b una
posición, de forma que el último elemento se convierte en el primero.*/
void	rrb(t_node **b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}

/*rra y rrb al mismo tiempo.*/
void	rrr(t_node **a, t_node **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}
