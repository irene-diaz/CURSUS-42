/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:25:23 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 11:38:09 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Libera toda la memoria de una pila (t_node *).
/*Para cuando salgamos del programa o tengamos que liberar recursos*/
void	free_stack(t_node **stack)
{
	t_node	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

// Devuelve el número de elementos en la pila.
/*La usaremos en sort_small() o para decidir que algoritmo vamos a usar y
tambien en ksort*/
int	stack_size(t_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

// Devuelve el último nodo de la pila.
/*Para decidir que operacion(ra, rra...) vamos a implementar*/
t_node	*stack_last(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

// Comprueba si la pila está ya ordenada(0: no, 1:si)
/*Para salir del programa sin hacer nada si ya esta todo ordenado*/
int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
