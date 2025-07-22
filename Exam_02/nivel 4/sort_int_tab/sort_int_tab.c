//#include <stdio.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *sort_list(t_list *lst, int (*cmp)(int, int))
{
    int temp;
    int swapped;
    t_list *head = lst;  // Guardamos la referencia al primer nodo de la lista

    // Verificamos si la lista está vacía o tiene un solo elemento
    if (lst == 0 || lst->next == 0)
        return lst;

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

    return head;  // Retornamos el inicio de la lista
}

/*unsigned int ft_strlen(int *str)
{
        int i=0;
        while(*str)
        {
            str++;
            i++;
        }
        return i;
}
int main(void)
{
    int arr[] = {5, 2, 8, 1, 3};
    unsigned int size = ft_strlen(arr);

    sort_int_tab(arr, size);

    for (unsigned int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}*/
