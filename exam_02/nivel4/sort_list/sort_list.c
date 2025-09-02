#include "list.h"

/*
	- lst: es el puntero al primer nodo de la lista enlazada.

	- cmp: es un puntero a una función de comparación que recibe dos int y devuelve:
	0 si los datos no están ordenados (hay que intercambiarlos),
	distinto de 0 si están bien ordenados.
*/

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*head;

	int tmp;    // Variable temporal para hacer el intercambio de datos
	head = lst; // Guardamos el puntero al inicio de la lista
	// Recorremos la lista mientras existan al menos dos nodos para comparar
	while (lst != 0 && lst->next != 0)
	{
		// Usamos la función de comparación para ver si los elementos están mal ordenados
		if ((*cmp)(lst->data, lst->next->data) > 0) // Cambié == 0 por > 0
		{
			// Si están mal ordenados, intercambiamos los datos de los nodos
			tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
			// Después de un intercambio, volvemos al inicio de la lista
			lst = head;
			// Reiniciamos lst para comparar todos los nodos desde el inicio
		}
		else
			// Si están bien ordenados, seguimos al siguiente par
			lst = lst->next;
	}
	// Devolvemos el puntero al inicio de la lista ya ordenada
	return (head);
}

/*#include <stdio.h>
#include <stdlib.h>

// Función de comparación ascendente
int	ascending(int a, int b)
{
	return (a - b);
}

// Función de comparación descendente
int	descending(int a, int b)
{
	return (b - a);
}

// Crea un nuevo nodo con un valor
t_list	*new_node(int value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = value;
	node->next = NULL;
	return (node);
}

// Imprime la lista
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d ", lst->data);
		lst = lst->next;
	}
	printf("\n");
}

int	main(void)
{
	// Creamos la lista: 5 -> 3 -> 8 -> 1 -> NULL
	t_list *head = new_node(5);
	head->next = new_node(3);
	head->next->next = new_node(8);
	head->next->next->next = new_node(1);

	printf("Lista original:\n");
	print_list(head);

	// Orden ascendente
	head = sort_list(head, ascending);
	printf("Lista ordenada ascendente:\n");
	print_list(head);

	// Orden descendente
	head = sort_list(head, descending);
	printf("Lista ordenada descendente:\n");
	print_list(head);

	return (0);
}*/
