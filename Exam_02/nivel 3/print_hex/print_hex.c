#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}
void print_hex(int number)
{
    char *alphabet= "0123456789abcdef";
    //si el numero es mayor o igual que 16, significa que es divisible por 16, lo dividimos de forma recursiva
    if(number>=16)
     print_hex(number/16);
    //mostramos el numero o letra que corresponde dentro del alfabeto hexadecimal
    ft_putchar(alphabet[number%16]);
}

int ft_atoi(char *nb)
{
    int i=0;
    int result=0;
    //mientras que el string sea un numero, transformalo a int
     while (nb[i] >= '0' && nb[i] <= '9')
     {
         result = result * 10 + (nb[i] - '0');
         i++;
     }
     return (result);
    
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        //para poder imprimir el numero en hexadecimal, primero tenemos que pasar el string a int, y esto lo hacemos con atoi
        int number= ft_atoi(argv[1]);
        print_hex(number);
       
    }
    write(1, "\n", 1);
}
