#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	char c;
	// palabra que queremos sustituir
	char *pat = argv[1];
	// longitud de esa palabra
	size_t plen = strlen(pat);
	// cuántos caracteres del patrón ya hemos comprobado (prefijo coincidente)
	size_t i = 0;

	ssize_t r;

	// Ese while está leyendo la entrada estándar carácter por carácter hasta que no haya más (EOF) o ocurra un error.
	while ((r = read(0, &c, 1)) > 0)
	{
		// si el caracter leido es igual al del patron, sumamos 1 al contador
		if (c == pat[i])
		{
			i++;
			// si el contador es igual a la longitud del patron
			if (i == plen)
			{
				size_t j = 0;
				// mientras recorramos el patron
				while (j < plen)
				{
					// escribimos *
					write(1, "*", 1);
					j++;
				}
				i = 0; // para no mostrar el caracter como tal
			}
		}
		else
		{
			// si el contador es mas que 0,quiere decir que el patron no es igual
			if (i > 0)
			{
				write(1, pat, i); // escribir coincidencia parcial
				i = 0;
			}
			write(1, &c, 1);
		}
	}
	// Si read devolvió error, lo reportamos y salimos con 1.
	if (r < 0)
	{
		perror("Error");
		return (1);
	}
	return (0);
}