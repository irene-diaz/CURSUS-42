#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (*str)
    {
        str++;
        i++;
    }
    return i;
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int first_space = 0;
        int j = ft_strlen(argv[1]) - 1;

        // Eliminar los espacios al final
        while (is_space(argv[1][j]))
        {
            j--;
        }

        int i = 0;
        // Eliminar los espacios al principio
        while (is_space(argv[1][i]))
        {
            i++;
        }

        // Recorrer la cadena
        while (i <= j)
        {
            if (is_space(argv[1][i]))
            {
                write(1, "   ", 3);
                while(is_space(argv[1][i]))
                {
                   i++;
                }
            }
            // Imprimir el carácter
            write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);  // Nueva línea al final
    return 0;
}
