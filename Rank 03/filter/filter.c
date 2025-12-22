#include <stdio.h>
#include <string.h>
#include <unistd.h>


int	main(int argc, char **argv)
{
	// Comprobamos que se haya introducido un argumento y que no sea un string vacio y que sea un solo argumento
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	char c;
	// Variable para almacenar cada carácter leído de stdin.
	char *pat = argv[1];       // El patrón a buscar (ej. "abc").
	size_t plen = strlen(pat); // longitud de esa palabra
	// cuántos caracteres del patrón ya hemos comprobado (prefijo coincidente)
	size_t i = 0;
	// valor de retorno del read (para controlar errores debemos usar ssize_t)
	ssize_t r;

	// Ese while está leyendo la entrada estándar carácter por carácter hasta que no haya más (EOF) o ocurra un error.
	/*Leemos de stdin (fd = 0) un carácter cada vez.
	read devuelve:
		1 → leímos un carácter.
		0 → EOF (fin de archivo).
		<0 → error.*/
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
					printf("*");
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
				printf("%.*s", (int)i, pat);
				// Escribe los primeros i caracteres de pat
				i = 0;
				// comprobamos si el caracter es el principio del patron
				if (c == pat[0])
				{
					i = 1;
					continue ;
				}
			}
			printf("%c", c);
		}
	}
	// Si read devolvió error, lo reportamos y salimos con 1.
	if (r < 0)
	{
		perror("Error: ");
		return (1);
	}
	// Agregado: manejar coincidencias parciales al final de la entrada
	if (i > 0)
	{
		printf("%.*s", (int)i, pat);
	}
	return (0);
}