#include "list.h"
/* 
    - lst: es el puntero al primer nodo de la lista enlazada.

    - cmp: es un puntero a una función de comparación que recibe dos int y devuelve:
    0 si los datos no están ordenados (hay que intercambiarlos),
    distinto de 0 si están bien ordenados.
*/

t_list *sort_list(t_list *lst, int (*cmp)(int, int))
{
    int tmp;                // Variable temporal para hacer el intercambio de datos
    t_list *head;

    head = lst;             // Guardamos el puntero al inicio de la lista

    // Recorremos la lista mientras existan al menos dos nodos para comparar
    while (lst != NULL && lst->next != NULL)
    {
        // Usamos la función de comparación para ver si los elementos están mal ordenados
        if ((*cmp)(lst->data, lst->next->data) > 0)  // Cambié == 0 por > 0
        {
            // Si están mal ordenados, intercambiamos los datos de los nodos
            tmp = lst->data;
            lst->data = lst->next->data;
            lst->next->data = tmp;

            // Después de un intercambio, volvemos al inicio de la lista
            lst = head;   // Reiniciamos lst para comparar todos los nodos desde el inicio
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
	return (a <= b);
    /*if (a<=b)
        return 1
    else
        return 0/*
}*/
