#include <unistd.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char *argv[])
{
	int i;
	int word;
	int j;

	if (argc == 2)
	{
		i = 0;
		word = 0;
		int starts[100]; // guarda inicios de palabras
		int ends[100];   // guarda finales de palabras
		while (argv[1][i])
		{
			// saltar espacios iniciales
			while (argv[1][i] && is_space(argv[1][i]))
				i++;
			if (argv[1][i]) // si hay palabra
			{
				starts[word] = i; // inicio
				while (argv[1][i] && !is_space(argv[1][i]))
					i++;
				ends[word] = i; // final (exclusivo)
				word++;
			}
		}
		// imprimir en orden inverso
		for (int w = word - 1; w >= 0; w--)
		{
			j = starts[w];
			while (j < ends[w])
			{
				write(1, &argv[1][j], 1);
				j++;
			}
			if (w > 0) // espacio entre palabras
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
}