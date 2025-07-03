#include <stdio.h>

// Definición de una estructura de lista enlazada
typedef struct    s_list
{
    struct s_list *next; // Puntero al siguiente nodo de la lista
    void          *data; // Puntero a los datos almacenados (tipo genérico)
}                 t_list;

// Función que aplica una función 'f' a cada elemento 'data' de una lista
void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    // Recorremos la lista mientras no lleguemos al final (NULL)
    while(begin_list != NULL)
    {
        // Si el nodo actual contiene datos
        if(begin_list->data != NULL)
        {
            // Aplicamos la función 'f' al contenido del nodo
            (*f)(begin_list->data);
        }

        // Avanzamos al siguiente nodo de la lista
        begin_list = begin_list->next;
    }
}