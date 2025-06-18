
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{

    if (ac == 3)
    {
        //convertimos los string a numeros
        int number1 = atoi(av[1]);
        int number2 = atoi(av[2]);
        
        //solo hacemos el mcd si son numeros positivos
        if (number1 > 0 && number2 > 0)
        {
            /*ALGORITMO DE EUCLIDES POR RESTAS SUCESIVAS*/
            //Mientras los dos números no sean iguales
            while (number1 != number2)
            {
                //resta el mayor menos el menor.
                //si n1 es mayor que n2 la resta sera n1-n2
                if (number1 > number2)
                    number1 = number1 - number2;
                //si n2 es mayor que n1 la resta sera n2-n1
                else
                    number2 = number2 - number1;
            }
            //imprimimos el maximo comun divisor, el cual por esta tecnica es cuando los dos numeros son iguales
            printf("%d", number1);
        }
    }
    printf("\n");
}