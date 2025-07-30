/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:41:36 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 12:30:27 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Intercambia los dos primeros elementos del stack correspondiente.
No hace nada si hay uno o menos elementos.*/
void	swap(t_node **stack)
{
	t_node	*first;
	t_node	*second;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

/*Toma el primer elemento del stack b y lo pone el primero en el stack a.
No hace nada si b está vacío (Esto lo hace igual con ambos stacks)*/
void	push(t_node **src, t_node **dest)
{
	t_node	*tmp;

	if (!*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

/*Desplaza hacia arriba todos los elementos del stack correspondiente una
posición, de forma que el primer elemento se convierte en el último.*/
void	rotate(t_node **stack)
{
	t_node	*first;
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	*stack = first->next;
	first->next = NULL;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
}

/*Desplaza hacia abajo todos los elementos del stack correspondiente una
posición, de forma que el último elemento se convierte en el primero.
Inicializamos prev en nulo por si solo hacemos la rotacion con 2 elementos*/
void	reverse_rotate(t_node **stack)
{
	t_node	*prev;
	t_node	*last;

	prev = NULL;
	if (!*stack || !(*stack)->next)
		return ;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}
