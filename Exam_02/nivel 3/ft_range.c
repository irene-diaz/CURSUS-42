#include <stdlib.h>

// Función que devuelve un array de enteros con los valores entre `end` y `start` (ambos incluidos),
// en orden descendente desde `end` hasta `start`
int *ft_range(int start, int end)
{
    int *nb;
    int len = 0;

    // Calculamos la longitud del array sumando 1 para incluir tanto start como end
    if (end >= start)
    {
        len = end - start + 1;
    }
    else
    {
        len = start - end + 1;
    }

    // Reservamos memoria para el array dinámico de enteros
    nb = malloc(len * sizeof(int));
    if (!nb) // Si la reserva falla, devolvemos NULL
    {
        return NULL;
    }

    int i = 0;

    // Caso en que end es mayor o igual que start: vamos desde end decrementando
    if (start <= end)
    {
        while (start <= end)
        {
            nb[i] = start;  // Guardamos el valor actual
            start++;        // Decrementamos hacia start
            i++;          // Pasamos al siguiente índice
        }
    }
    else // Caso en que start > end: vamos desde end incrementando hasta start
    {
        while (start >= end)
        {
            nb[i] = start;  // Guardamos el valor actual
            start--;        // Incrementamos hacia start
            i++;          // Pasamos al siguiente índice
        }
    }

    // Devolvemos el array dinámico ya llenado
    return nb;
}


/*#include <stdio.h>

int main(void)
{
    int *arr = ft_range(1, 3);
    for (int i = 0; i < 3; i++)
        printf("%d ", arr[i]); // Output: 1 2 3
    free(arr);

    arr = ft_range(0, -3);
    for (int i = 0; i < 4; i++)
        printf("%d ", arr[i]); // Output: 0 -1 -2 -3
    free(arr);

    return 0;
}*/
