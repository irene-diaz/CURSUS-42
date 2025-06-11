#include <unistd.h>

// te dice si un carácter es espacio o tabulación.
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	int i = 0;
	// indica si estas dentro de una palabra o no(1 si 0 no)
	int in_word = 0;
	// para evitar imprimir espacios antes de la primera palabra.(1, ya la hemos impreso 0, todavia no)
	int first_word = 1;

	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (!is_space(argv[1][i])) // estamos en una letra(no es un espacio ni tab)
			{
                //Si NO es la primera palabra y actualmente NO estamos dentro de una palabra, entonces escribe 3 espacios.
				if (!first_word && !in_word)
					write(1, "   ", 3); // solo entre palabras
				
                //imprimimos la letra actual
                write(1, &argv[1][i], 1);
                //marcamos que ahora estamos dentro de una palabra
				in_word = 1;
                //maracamos que ya no estamos en la primera palabra
				first_word = 0;
			}
			else // espacio o tab
			{
				in_word = 0; // salimos de palabra
			}
			i++;
		}
	}

	write(1, "\n", 1);
	return (0);
}