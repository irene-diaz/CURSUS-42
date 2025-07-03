#include <unistd.h>

int i=0;

int ft_strlen(char *str)
{   
    while(*str)
    {
        str++;
        i++;
    }
    return i;
}

int is_space(char c)
{
    if(c==' ' || c=='\t')
    {
        return 1;
    }
    else{
        return 0;
    }
}
int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        //cogemos la longitud de la cadena, sin contar el final de linea
        int i = ft_strlen(argv[1]) - 1;

        // Saltar espacios al final
        while (is_space(argv[1][i]))
            i--;

        // Retroceder hasta encontrar un espacio o el inicio de la cadena
        while (!is_space(argv[1][i]))
            i--;

        // Imprimir la última palabra
        while (argv[1][i])
        {
            write(1, &argv[1][i], 1);
            i++;
        }
    }

    // Siempre imprimimos \n
    write(1, "\n", 1);
    return 0;
}