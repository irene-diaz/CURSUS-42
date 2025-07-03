#include <stdlib.h>
//#include <stdio.h>

int     *ft_range(int start, int end)
{
    int *array;

    //calculamos la longitud que necesitamos que tenga el nuevo array(el +1 es obligatorio)
    int len= (end - start) +1;

    //reservamos memoria para el nuevo array (lo del sizeof es necesario, ya que un int ocupa 4 bytes)
    array= malloc(len * sizeof(int));
   
    if(!array)
    {
        return NULL;
    }

    int i=0;
    //recorremos el array desde start hasta end
    while(start <= end)
    {
        //guardamos todos los numeros hasta el final
        array[i]=start;
        start++;
        i++;
    }

    //devolvemos un array con todos los numeros que hay dentro de ese rango
    return array;
}

/*int main(int argc, char *argv[])
{
    
    int start=atoi(argv[1]);
    int end=atoi(argv[2]);
    int *array= ft_range(start, end);

    if(!array)
    {
        return 0;
    }

    int i=0;
    int len= (end - start)+1;
    while(i<len)
    {
        printf("%d ", array[i]);
        i++;
    }

    //liberamos memoria
    free(array);

}*/