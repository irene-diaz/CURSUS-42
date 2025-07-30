/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:41:43 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 12:41:19 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*ksort es una variante del algoritmo de ordenación por inserción usando índices
y dos stacks (a y b). La idea principal es:

	Mover los elementos con los índices más pequeños desde a a b en bloques
	(“chunks”).

	Una vez que los tengas en b,
		los devuelves a a ordenadamente (el más grande arriba).
*/

// encontrar el mayor indice
static int	find_max_index(t_node *stack)
{
	int	max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

// busca en qué posición está un nodo con el índice dentro de la pila(stack).
/*Esta funcion la utilizamos para saber cuantas veces tiene que rotar(rb o rrb)
  para llevar el nodo arriba. Es una función clave en push_back_max(),
  para saber si te conviene rotar hacia arriba (rb) o hacia abajo (rrb).*/
static int	find_index_pos(t_node *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

/* Esta función busca el elemento con el mayor índice en b, lo sube a la cima,
	y lo pasa a a.*/
/*DESGLOSE DE LA FUNCION
	1º. BUSCA EL INDICE MAS ALTO EN B
	2º. CALCULA EN QUE POSICION ESTA
	3º. SI ESTAMOS EN LA PRIMERA MITAD ROTAMOS HACIA ARRIBA HASTA LLEGAR A ARRIBA
	DEL TODO Y SINO LO ESTA ROTAMOS HACIA ABAJO
	4º. PASAMOS EL NUMERO FINAL DE B a A*/
static void	push_back_max(t_node **a, t_node **b)
{
	int	max;
	int	pos;
	int	size;

	max = find_max_index(*b);
	pos = find_index_pos(*b, max);
	size = stack_size(*b);
	if (pos <= size / 2)
	{
		while ((*b)->index != max)
			rb(b);
	}
	else
	{
		while ((*b)->index != max)
			rrb(b);
	}
	pa(a, b);
}

/*OBJETIVO DEL KSORT
Ordenar una lista de números usando solo las operaciones permitidas (sa, pb, pa,
ra, etc.). Lo hace:

	1. Dividiendo el stack a en bloques (“chunks”) de índices.

	2. Enviando esos bloques a b, con rotaciones para mantenerlo más ordenado.

	3. Luego devuelve el contenido de b a a, del mayor al menor, ya ordenado.*/
/**
 * ksort - Algoritmo de ordenación basado en "chunks" usando índices.
 *
 * Esta función divide el stack 'a' en bloques (chunks) según los índices
 * de los elementos ya asignados previamente. Envía los elementos de menor
 * índice al stack 'b' y rota cuando conviene para optimizar el orden.
 * Una vez vacío 'a', se reconstruye de forma ordenada devolviendo
 * los elementos desde 'b' al stack 'a' del mayor al menor.
 *
 * chunk: define el tamaño del bloque de índices que se van enviando.
 * Este valor puede ajustarse según la cantidad de números a ordenar.
 */
void	ksort(t_node **a, t_node **b)
{
	int	i;
	int	chunk;

	chunk = 15;
	i = 0;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			pb(a, b);
			rb(b);
			i++;
		}
		else if ((*a)->index <= i + chunk)
		{
			pb(a, b);
			i++;
		}
		else
			ra(a);
	}
	while (*b)
		push_back_max(a, b);
}
