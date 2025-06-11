#include <unistd.h>

// Verifica si el carácter ya fue mostrado antes en el string hasta la posición pos
int already_printed(char *str, char c, int pos)
{
    int i = 0;
    while (i < pos)
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

void    ft_union(char *s1, char *s2)
{
    int i = 0;
    int j;

    // Imprimir caracteres únicos de s1
    while (s1[i])
    {
        if (!already_printed(s1, s1[i], i))
            write(1, &s1[i], 1);
        i++;
    }

    // Imprimir caracteres únicos de s2 que no están en s1
    j = 0;
    while (s2[j])
    {
        if (!already_printed(s2, s2[j], j) && !already_printed(s1, s2[j], i))
            write(1, &s2[j], 1);
        j++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 3)
        ft_union(argv[1], argv[2]);
    write(1, "\n", 1);
    return 0;
}