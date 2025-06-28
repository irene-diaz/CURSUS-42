#include <stdio.h>

/* Esta función cuenta cuántos caracteres consecutivos desde el principio de 's'
están presentes dentro de la cadena 'accept'.*/
size_t ft_strspn(const char *s, const char *accept)
{
    size_t i = 0;     // Índice para recorrer la cadena 's'
    int found;        // Bandera para indicar si el carácter actual de 's' está en 'accept'

    // Recorremos la cadena 's' carácter por carácter
    while (s[i])
    {
        found = 0;    // Reiniciamos la bandera cada vez que analizamos un nuevo carácter de 's'

        // Recorremos la cadena 'accept' para ver si el carácter actual de 's' está dentro de 'accept'
        for (size_t j = 0; accept[j]; j++)
        {
            if (s[i] == accept[j]) // Si encontramos coincidencia
            {
                found = 1;         // Marcamos como encontrado
                break;             // Salimos del bucle porque ya sabemos que está en 'accept'
            }
        }

        // Si el carácter actual de 's' no está en 'accept', devolvemos el índice actual (fin de secuencia válida)
        if (!found)
            return i;

        i++; // Avanzamos al siguiente carácter de 's'
    }

    // Si todos los caracteres de 's' estaban en 'accept', devolvemos la longitud recorrida
    return i;
}

/*int main(void)
{
    const char *s = "abcde12345";
    const char *accept = "abcde";

    printf("%zu\n", ft_strspn(s, accept)); // Resultado: 5 (porque 'abcde' está en accept, pero '1' no)
}*/