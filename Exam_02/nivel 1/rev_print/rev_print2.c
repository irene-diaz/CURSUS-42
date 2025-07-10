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
// Imprime al revés, pero devuelve el mismo puntero original
char *rev_print(char *str)
{
    int len = ft_strlen(str) - 1;
    while (len >= 0)
    {
        write(1, &str[len], 1);
        len--;
    }
    return str;  // Devolver el mismo puntero recibido
}

int main(void)
{
    char *str = rev_print("Hola mundo"); // imprime: "odnum aloH"
    write(1, "\n", 1);

    // Ahora puedes usar str si quieres (será igual a "Hola mundo")
    int i = 0;
    while (str[i])
    {
        write(1, &str[i], 1); // imprime: "Hola mundo"
        i++;
    }

    write(1, "\n", 1);
    return 0;
}