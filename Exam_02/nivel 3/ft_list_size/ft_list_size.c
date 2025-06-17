typedef struct    s_list
{
    struct s_list *next; //Apunta al siguiente nodo de la lista
    void          *data; //Apunta a los datos del nodo(puede ser cualquier cosa)
}   t_list;

int	ft_list_size(t_list *begin_list)
{
    int i;

    i=0;
    /*Mientras el nodo actual (begin_list) no sea NULL:
    Avanzas al siguiente nodo: begin_list = begin_list->next
    Aumentas el contador i++*/
    while(begin_list)
    {
        begin_list= begin_list->next; //es como poner una funcion normal begin_list++
        i++;  
    }
    //devuelves la cantidad de nodos
    return i;
}