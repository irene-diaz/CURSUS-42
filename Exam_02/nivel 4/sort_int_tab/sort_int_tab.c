//#include <stdio.h>

void sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i;
    //temp: variable auxiliar para intercambiar dos números.
    int temp;
    //swapped: bandera para saber si se hizo algún intercambio en el bucle (si no, la lista ya está ordenada).
    int swapped;

    //Si el array tiene menos de 2 elementos, ya está ordenado, no hacemos nada.
    if (size < 2)
        return;

    //Comienza un ciclo do-while que se repetirá mientras se hagan intercambios (swapped = 1).
    do {
        //inizializamos la variable 0, pq no hay intercambios
        swapped = 0;
        i = 0;
        //recorremos el array y lo que hacemos es comparamos cada par de elementos consecutivos
        while (i < size - 1)
        {
            //aqui es donde vemos la comparacion de los elementos consecutivos
           //Si el actual (tab[i]) es mayor que el siguiente (tab[i + 1]), los intercambiamos.
            if (tab[i] > tab[i + 1])
            {
                // Intercambiar elementos
                //igualamos el primer valor a la variable temporal
                temp = tab[i];
                //igualamos el primer vakor al segundo valor
                tab[i] = tab[i + 1];
                //igualamos el segundo valor a la variable temporal
                tab[i + 1] = temp;
                //Si al menos un intercambio ocurre, swapped = 1 → el bucle se repetirá.
                swapped = 1;
            }
            i++;
        }
    /*Se repite mientras se hayan hecho intercambios.
    Cuando ya no se necesita intercambiar nada, el array está ordenado.*/
    }while (swapped);
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