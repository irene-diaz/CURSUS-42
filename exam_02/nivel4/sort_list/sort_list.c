#include "list.h"
#include <stdlib.h>

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
	while (lst != NULL && lst->next != NULL)
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

/*int ascending(int a, int b)
{
	int	temp;
	int	swapped;

	return (a <= b);
	/*if (a<=b)
		return 1
	else
		return 0/*
}*/
/*2º OPCION
t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list *head = lst;  // Guardamos la referencia al primer nodo de la lista
	// Verificamos si la lista está vacía o tiene un solo elemento
	if (lst == 0 || lst->next == 0)
		return (lst);
	do {
		swapped = 0;
		// Recorremos la lista comparando los nodos adyacentes
		while (lst != 0 && lst->next != 0) {
			if ((*cmp)(lst->data, lst->next->data) > 0) {
				// Intercambiamos los datos de los nodos
				temp = lst->data;
				lst->data = lst->next->data;
				lst->next->data = temp;
				swapped = 1;  // Indicamos que hubo un intercambio
			}
			lst = lst->next;  // Avanzamos al siguiente nodo
		}
		// Reiniciamos el puntero lst al principio de la lista
		lst = head;
	} while (swapped);  // Repetimos el proceso si hubo intercambios
	return (head);  // Retornamos el inicio de la lista
}
*/
