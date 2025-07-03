#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("\n");
    }
    else{
        int n= atoi(argv[1]);
        int i=2;

        //si n es 1, su unico factor sera 1
        if(n==1)
        {
            printf("1");
        }

        //mientras el numero se pueda factorizar
        while (n > 1)
        {
            //mientras se pueda dividir y sea exacta la division
            if (n % i == 0)
            {
                //imprimimos el factor
                printf("%d", i);
                //lo dividimos y asi sucesivamente
                n /= i;
                //cada vez que imprimamos un factor ponemos * a noser que sea un 1(pq esto quiere decir que no tiene mas factores)
                if (n != 1)
                    printf("*");
            }
            else
            {
                //si no es divisble pasamos de ese numero, pq no sera un factor
                i++;
            }
        }

        printf("\n");

    }
}
