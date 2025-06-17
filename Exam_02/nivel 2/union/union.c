#include <unistd.h>

// Verifica si el carácter c ya fue mostrado antes en el string str hasta la posición pos
int already_printed(char *str, char c, int pos)
{
    int i = 0;
    // Recorremos el string desde el inicio hasta la posición pos
    while (i < pos)
    {
        // Si encontramos el carácter c antes de pos, devolvemos 1 (ya fue mostrado)
        if (str[i] == c)
            return 1;
        i++;
    }
    // Si no se encontró el carácter antes, devolvemos 0 (no ha sido mostrado)
    return 0;
}

// Imprime la unión de caracteres únicos de s1 y s2
void ft_union(char *s1, char *s2)
{
    int i = 0;
    int j;

    // Imprimir caracteres únicos de s1
    while (s1[i])
    {
        // Si el carácter s1[i] no ha sido mostrado antes en s1 hasta la posición i, lo imprimimos
        if (!already_printed(s1, s1[i], i))
            write(1, &s1[i], 1);
        i++;
    }

    // Imprimir caracteres únicos de s2 que no están en s1
    j = 0;
    while (s2[j])
    {
        // Solo imprimimos s2[j] si:
        // 1) No se ha mostrado antes en s2 (hasta j)
        // 2) No está ya en s1 (usando i que es la longitud de s1)
        if (!already_printed(s2, s2[j], j) && !already_printed(s1, s2[j], i))
            write(1, &s2[j], 1);
        j++;
    }
}

int main(int argc, char **argv)
{
    // Solo si tenemos exactamente dos argumentos, hacemos la unión
    if (argc == 3)
        ft_union(argv[1], argv[2]);
    write(1, "\n", 1);
    return 0;
}
