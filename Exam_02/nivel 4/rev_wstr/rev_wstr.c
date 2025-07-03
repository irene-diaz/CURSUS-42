#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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


// Cuenta palabras y guarda los inicios de cada una en el array
int count_words(char *str, char **starts)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (!is_space(str[i]) && (i == 0 || is_space(str[i - 1])))
        {
            //Guarda un puntero al inicio de cada palabra en el arreglo starts.
            starts[count] = &str[i];
            count++;
        }
        i++;
    }
    return count;
}

// Escribe una palabra hasta encontrar espacio o fin de string
void print_word(char *str)
{
    int i = 0;
    //Imprime los caracteres desde str hasta que encuentra un espacio o fin de string (\0):
    while (str[i] && !is_space(str[i]))
    {
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(1, "\n", 1);
        return 0;
    }

    char *starts[1000]; // array de inicios de palabras
    int word_count = count_words(argv[1], starts); //Cuenta las palabras y llena el arreglo starts con los inicios de cada una.

    //Recorre las palabras en orden inverso
    int i = word_count - 1;
    while (i >= 0)
    {
        print_word(starts[i]);
        if (i > 0)
        {
            write(1, " ", 1);// Imprime espacio entre palabras
        }
        i--;
    }
    write(1, "\n", 1);
    return 0;
}