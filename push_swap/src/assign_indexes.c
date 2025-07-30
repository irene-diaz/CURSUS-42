/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oem <oem@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:00:23 by oem               #+#    #+#             */
/*   Updated: 2025/07/30 12:40:58 by oem              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// funcion de intercambio de valores
static void	swap_values(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// funcion de ordenacion burbuja
static void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (arr[j] > arr[j + 1])
				swap_values(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

// asigamos a cada nodo su indice
/**DESGLOSE DE LA FUNCION
	1º RECORREMOS TODOS LOS NODOS DEL STACK
	2º BUSCAMOS EN EL ARRAY ORDENADO(buble sort) DONDE APARECE SU VALOR
	3º CUANDO ENCONTRAMOS SU VALOR LE ASIGNAMOS COMO INDICE SU POSICION ORDENADA
	4º PASAMOS LA SIGUIENTE NODO HASTA QUE NO HAYA MAS NODOS EN EL STACK
**/
static void	index_stack(t_node *stack, int *arr, int size)
{
	int	i;

	while (stack)
	{
		i = 0;
		while (i < size)
		{
			if (stack->value == arr[i])
			{
				stack->index = i;
				break ;
			}
			i++;
		}
		stack = stack->next;
	}
}

// recorre cada nodo y le asigna su índice (posición en el array ordenado).
/**DESGLOSE DE LA FUNCION
	1º RESERVAMOS EL ESPACIO DE MEMORIA DEL ARRAY
	2º COPIAMOS LOS VALORES DE LA PILA AL ARRAY
	3º ORDENAMOS EL ARRAY(en este caso con ordenacion burbuja)
	4º ASIGNAMOS EL INDICE ORDENADO A CADA NODO
	5º LIBERAMOS LA MEMORIA ASIGNADA AL ARRAY
**/
void	assign_indexes(t_node *stack)
{
	int		*arr;
	int		size;
	t_node	*tmp;
	int		i;

	size = stack_size(stack);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		error_and_exit();
	tmp = stack;
	i = 0;
	while (i < size)
	{
		arr[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	bubble_sort(arr, size);
	index_stack(stack, arr, size);
	free(arr);
}
