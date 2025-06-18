#include <unistd.h>

// revisa si el carácter c ya apareció antes en str hasta la posición i.
int has_char(char *str, char c, int limit)
{
    int i = 0;
    while (i < limit)
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}
// revisa si c existe en str2.
int in_str(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int i = 0;
        while (argv[1][i])
        {
            //si el caracter no ha aparecido antes y esta en str2, muestralo
            if (in_str(argv[2], argv[1][i]) && !has_char(argv[1], argv[1][i], i))
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}