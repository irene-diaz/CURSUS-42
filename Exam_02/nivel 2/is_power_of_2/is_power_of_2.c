#include <stdio.h>

int is_power_of_2(unsigned int n)
{
    if (n == 0)
        return 0;

    while (n % 2 == 0)  // mientras sea divisible por 2
    {
        n = n / 2;
    }

    return (n == 1); // si al final queda 1, sí era potencia de 2
}

/*con recursividad seria asi:
#include <stdio.h>

int is_power_of_2(unsigned int n)
{
    if (n == 0)            // Caso base 1: 0 no es potencia de 2
        return 0;
    if (n == 1)            // Caso base 2: 1 sí es potencia de 2 (2^0)
        return 1;
    if (n % 2 != 0)        // Si no es divisible por 2 → falso
        return 0;
    return is_power_of_2(n / 2);  // Llamada recursiva
}
*/

/*int main(void)
{
    printf("%d\n", is_power_of_2(8));  // 1 (true)
    printf("%d\n", is_power_of_2(6));  // 0 (false)
    printf("%d\n", is_power_of_2(5));  // 0 (false)
    printf("%d\n", is_power_of_2(1));  // 1 (true, 2^0)
}*/