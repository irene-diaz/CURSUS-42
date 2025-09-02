#include <unistd.h>

int	is_space(char c)
{
	if (c == '\t' || c == ' ')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
int	main(int argc, char *argv[])
{
	int i;
	int start_first;
	int end_first;
	int end = 0;
	int start = 0;
	// variable boolean para saber si se han mostrado palabras(1) o no(0)
	int printed = 0;

	// hacemos todo en el caso de que haya al menos 2 argumentos
	if (argc >= 2)
	{
		i = 0;

		/*LOGICA PARA GUARDAR LA PRIMERA PALABRA*/
		// saltamos espacios inciales
		while (is_space(argv[1][i]))
		{
			i++;
		}
		// guardamos el principio de la primera palabra
		start_first = i;
		// recorremos toda la primera palabra
		while (argv[1][i] && !is_space(argv[1][i]))
		{
			i++;
		}
		// guardamos el final de la primera palabra
		end_first = i;

		/*LOGICA PARA GUARDAR EL RESTO DE PALABRAS*/
		// saltamos espacios inciales
		while (is_space(argv[1][i]))
		{
			i++;
		}
		// guardamos el principio de la segunda palabra
		start = i;
		// recorremos todas las palabras(excepto la primera)
		while (argv[1][i])
		{
			i++;
		}
		// guardamos el final de todo el str(argv[1])
		end = i;

		/*LOGICA PARA RECORRER Y MOSTRAR TODAS LAS PALABRAS*/
		while (start < end)
		{
			// si hay un espacio escribimos otro
			if (is_space(argv[1][start]))
			{
				write(1, " ", 1);
			}
			// saltamos todos los espacios(para solo dejar el que escribimos con el write por cada palabra)
			while (is_space(argv[1][start]))
			{
				start++;
			}
			// mostramos todas las palabras
			write(1, &argv[1][start], 1);
			start++;
			// ponemos el boolean en true, ya que hemos mostrado alguna palabra
			printed = 1;
		}
		/*MOSTRAMOS UN ESPACIO SI ANTES YA HEMOS MOSTRADO UNA PALABRA*/
		if (printed == 1)
		{
			write(1, " ", 1);
		}
		/*LOGICA PARA RECORRER Y MOSTRAR LA PRIMERA PALABRA COMO LA ULTIMA*/
		while (start_first < end_first)
		{
			// mostramos la palabra
			write(1, &argv[1][start_first], 1);
			start_first++;
		}
	}
	write(1, "\n", 1);
}