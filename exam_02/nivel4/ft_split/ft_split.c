#include <stdlib.h>
#include <stdio.h>

int is_space(char c)
{
    if(c=='\n' || c=='\t' || c==' ')
    {
        return 1;
    }
    else{
        return 0;
    } 
}

int count_words(char *str)
{
    int i=0;
    int cont=0;
    while(is_space(str[i]))
    {
        i++;
    }
    while(str[i])
    {
        if(is_space(str[i-1])||i==0)
        {
            cont++;
        }
        i++;
    }
    return cont;
}

//copia una palabra de str desde start hasta end
char *copy_word(char *str, int start, int end)
{
    char *word = malloc(end - start + 1);  // +1 para el '\0' al final
    int i = 0;

    // Copia carácter a carácter desde str[start] hasta str[end - 1]
    while (start < end)
        word[i++] = str[start++];

    word[i] = '\0'; // Termina la cadena
    return word;
}
char    **ft_split(char *str)
{
    /*i: recorre toda la cadena str.

    j: posición actual en el array de resultados (result).

    start: índice donde comienza una palabra. -1 si no estás dentro de una palabra.*/

    int i = 0, j = 0, start = -1;
    int words = count_words(str);  // Cuenta cuántas palabras hay
    char **result = malloc(sizeof(char *) * (words + 1)); // Array de punteros a palabras
    
    while (str[i])
    {
        //Si el carácter actual no es espacio y no estábamos ya dentro de una palabra (start < 0), guardamos el índice de inicio.
        if (!is_space(str[i]) && start < 0)
            start = i; // Encontramos el inicio de una palabra
        //Si encontramos un espacio y estábamos dentro de una palabra (start >= 0), copiamos la palabra usando copy_word y reiniciamos start.
        else if (is_space(str[i]) && start >= 0)
        {
            result[j++] = copy_word(str, start, i);
            start = -1;
        }
        i++;
    }

    /*Esa condición if (start >= 0) comprueba:

    ¿Estábamos dentro de una palabra al llegar al final del string?

    Si sí, entonces significa que la última palabra aún no se copió.

    Así que hacemos:
    result[j++] = copy_word(str, start, i);

    Se usa i como fin, porque i apunta justo al final del string ('\0').*/
    if (start >= 0) // Última palabra al final de la cadena
    result[j++] = copy_word(str, start, i);
    result[j] = NULL; // Terminamos el array con NULL
    return result;
}

int main(void)
{
    //printf("%d", count_words("   Hola\tmundo\n42 "));
    char **result = ft_split("  hola\tmundo\n42   ");
    for (int i = 0; result[i]; i++)
        printf("Palabra %d: %s\n", i + 1, result[i]);
}