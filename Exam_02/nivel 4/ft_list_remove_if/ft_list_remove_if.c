// Definición de la estructura de lista enlazada simple
typedef struct      s_list
{
    struct s_list   *next; // Puntero al siguiente nodo
    void            *data; // Puntero genérico a los datos del nodo
}                   t_list;

#include "stdlib.h"

// Función que elimina de la lista todos los nodos cuyo contenido ('data')
// coincide con 'data_ref', comparado mediante la función 'cmp'
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *tmp;

    // Verifica si la lista o el puntero a la lista es NULL
	if ((*begin_list == NULL) || (begin_list == NULL))
		return ;

    // Compara el contenido del nodo actual con 'data_ref'
	if (cmp((*begin_list)->data, data_ref) == 0) // si son iguales
	{
        // Guarda el nodo actual en 'tmp' para poder liberarlo después
		tmp = *begin_list;

        // Hace que el puntero a la lista apunte al siguiente nodo
		*begin_list = (*begin_list)->next;

        // Libera el nodo actual
		free(tmp);

        // Llama recursivamente a la función para continuar con la lista
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
        // Si los datos no coinciden, avanza al siguiente nodo
        // Llama recursivamente con el puntero al campo next del nodo actual
		ft_list_remove_if(&((*begin_list)->next), data_ref, cmp);
	}
}