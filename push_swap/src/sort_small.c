/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:44:13 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 09:55:52 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Encontrar la posición del valor más pequeño en la pila.
static int	stack_min_pos(t_node *stack)
{
	int		pos;
	int		i;
	int		min;
	t_node	*tmp;

	pos = 0;
	i = 0;
	min = stack->value;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value < min)
		{
			min = tmp->value;
			pos = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (pos);
}

// Rotar la pila hasta que el nodo con el valor más pequeño quede arriba
/*Si estamos en la primera mitad, rotamos normal
Sino lo estamos, hacemos una rotacion inversa*/
static void	rotate_min_to_top(t_node **stack)
{
	int	pos;
	int	size;

	pos = stack_min_pos(*stack);
	size = stack_size(*stack);
	if (pos <= size / 2)
		while (pos--)
			ra(stack);
	else
		while (pos++ < size)
			rra(stack);
}

// ordena 3 numeros (solo hay 6 formas posibles)
static void	sort_three(t_node **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

// Ordenar cualquier pila de tamaño 2 a 5 elementos.

/*ORDENAR 4 ELEMENTOS
rotate_min_to_top(a);   // llevamos el más pequeño al top
pb(a, b);               // lo mandamos a b
sort_three(a);          // ordenamos los 3 restantes
pa(a, b);               // devolvemos el más pequeño*/

/*ORDENAR 5 ELEMENTOS
rotate_min_to_top(a);   // llevamos el más pequeño al top
pb(a, b);              // lo mandamos a b
rotate_min_to_top(a); // llevamos el más pequeño al top
pb(a, b);            // quitamos los dos más pequeños
sort_three(a);      // ordenamos los 3 restantes
pa(a, b); pa(a, b);// devolvemos los dos mínimos*/
void	sort_small(t_node **a, t_node **b)
{
	int	size;

	size = stack_size(*a);
	if (size == 2 && (*a)->value > (*a)->next->value)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else if (size == 4)
	{
		rotate_min_to_top(a);
		pb(a, b);
		sort_three(a);
		pa(a, b);
	}
	else if (size == 5)
	{
		rotate_min_to_top(a);
		pb(a, b);
		rotate_min_to_top(a);
		pb(a, b);
		sort_three(a);
		pa(a, b);
		pa(a, b);
	}
}
