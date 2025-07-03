#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 3)  // Si no hay 2 argumentos, solo imprime salto de línea
    {
        write(1, "\n", 1);
        return 0;
    }

    char *str1 = argv[1];  // cadena que queremos formar
    char *str2 = argv[2];  // cadena donde buscamos los caracteres
    int i = 0;  // índice para str1
    int j = 0;  // índice para str2

    while (str1[i] && str2[j]) // mientras no termine ninguna cadena
    {
        if (str1[i] == str2[j])
        {
            i++;  // encontramos el carácter que queremos, pasamos al siguiente en str1
        }
        j++;  // siempre avanzamos en str2 para mantener el orden
    }

    if (str1[i] == '\0')  // si llegamos al final de str1, significa que la encontramos entera
    {
        // imprimir str1 seguido de salto de línea
        i = 0;
        while (str1[i])
        {
            write(1, &str1[i], 1);
            i++;
        }
        write(1, "\n", 1);
    }
    else
    {
        write(1, "\n", 1);  // no se pudo formar str1 con str2
    }

    return 0;
}