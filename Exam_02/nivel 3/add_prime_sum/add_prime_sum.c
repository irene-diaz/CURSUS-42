#include <unistd.h>

//funcion para ver si c es un digito
int ft_isdigit(char c)
{
    if(c>='0' && c<='9') 
    {
        return 1;
    }
    else{
        return 0;
    }
}

//convertir un array de caracteres a numeros
int ft_atoi(char *str)
{
    int res=0;
    int i=0;
    while (ft_isdigit(str[i]))
    {
        res *= 10;
        res += str[i] - '0';
        i++;
    }
    return res;
}

//convertir de numero a array de caracteres
void ft_putnbr(int n)
{
    char c;
    if(n>=10)
    {
        ft_putnbr(n/10);
    }
    c= n%10 + '0';
    write(1, &c, 1);
}

//funcion que decide si un numero es primo o no(1 si, 0 no)
int is_prime(int n)
{
        int i=2;
        int cont=0;
        while(i<=n)
        {
           if(n%i==0)
           {
            cont++;
           }
           i++;
        }
        if(cont == 1)
        {
            return 1;
        }
        else{
            return 0;
        }
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int n = ft_atoi(argv[1]);
        int suma=0;

        int i=0;

        //vamos recorriendo el numero, y si es primo lo sumamos y asi sucesivamente
        while(i<=n)
        {
            if(is_prime(i))
            {
            suma+=i;
            }
            i++;
        }
        ft_putnbr(suma);
    }
    write(1, "\n", 1);
}

/*NUMEROS PRIMOS
2, 3, 5, 7, 11, 13, 17, 19, 23, 29*/