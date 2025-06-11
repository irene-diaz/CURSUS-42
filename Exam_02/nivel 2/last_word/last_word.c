#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int start;

    if (argc == 2)
    {
        // Avanzar hasta el final del string
        while (argv[1][i])
        {
            i++;
        }

        // Retrocedemos un caracter, para evitar quedarnos en ek final de caracter('\0')
        i--;

        // Retroceder para saltar espacios o tabs al final
        while (i >= 0 && (argv[1][i] == ' ' || argv[1][i] == '\t'))
            i--;

        // Marcar el final de la última palabra
        int end = i;

        // Retroceder hasta encontrar el espacio que la separa(el inicio de la palabra)
        while (i >= 0 && argv[1][i] != ' ' && argv[1][i] != '\t')
            i--;

        // Inicio está justo después del espacio
        start = i + 1;

        // Imprimir desde start hasta end
        while (start <= end)
        {
            write(1, &argv[1][start], 1);
            start++;
        }
    }

    // Siempre imprimimos \n
    write(1, "\n", 1);
    return 0;
}