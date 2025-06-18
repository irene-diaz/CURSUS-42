#include <unistd.h>

int ft_strlen(char *str)
{
    int i=0;
    while(*str)
    {
        str++;
        i++;
    }
    return i;
}
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        int len;
        /*Cuando queremos recorrer una cadena al revés, empezamos desde el último 
        carácter visible, que está en el índice length - 1.*/
        //cogemos la longitud -1 para que no cuente el final de linea
        len=ft_strlen(argv[1])-1;
        while(len>=0)
        {
            write(1, &argv[1][len], 1);
            len--;
        }
    }
    write(1,"\n", 1);
}