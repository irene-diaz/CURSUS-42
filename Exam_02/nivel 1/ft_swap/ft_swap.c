#include <stdio.h> // Incluimos la librería estándar para usar printf

// Esta función intercambia los valores de las variables a y b usando punteros
void	ft_swap(int *a, int *b)
{
    int temp;      // Variable temporal para guardar el valor original de *a

    temp = *a;     // Guardamos el valor apuntado por 'a' en 'temp'
    *a = *b;       // Asignamos a '*a' el valor que está en '*b'
    *b = temp;     // Asignamos a '*b' el valor original de '*a' guardado en 'temp'
}

/*int main(void)
{
    int a = 135;   // Declaramos una variable entera 'a' y la inicializamos a 135
    int b = 140;   // Declaramos una variable entera 'b' y la inicializamos a 140

    // Llamamos a la función ft_swap y pasamos las direcciones de 'a' y 'b'
    // Esto permite que la función modifique directamente los valores originales
    ft_swap(&a, &b);

    // Imprimimos el valor actual de 'a' y 'b' después del intercambio
    printf("a = %d\n", a); // Imprime 140, que era el valor original de 'b'
    printf("b = %d\n", b); // Imprime 135, que era el valor original de 'a'

    return 0; // Fin del programa
}*/