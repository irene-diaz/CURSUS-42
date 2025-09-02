#include <unistd.h>

int	iter(char *str, char c, int len)
{
	int	i;

	i = 0;
	// Recorre la cadena 'str' mientras:
	// 1) Haya caracteres (str[i] != '\0')
	// 2) Y además:
	//    - Si len != -1: solo recorre hasta la posición 'len - 1'
	//    - Si len == -1: recorre toda la cadena (sin límite)
	while (str[i] && (i < len || len == -1))
		// Si encuentra el carácter 'c' en la posición actual
		if (str[i++] == c)
			// Devuelve 1 (verdadero, encontrado)
			return (1);
	// Si terminó el bucle sin encontrar 'c', devuelve 0 (falso)
	return (0);
}

int	main(int argc, char *argv[])
{
	int i;
	int j;

	// El programa solo funciona si se pasan EXACTAMENTE 2 argumentos:
	// ./a.out string1 string2
	if (argc == 3)
	{
		i = 0;
		j = 0;
		// Recorremos cada carácter de argv[1] (el primer string)
		while (argv[1][i])
		{
			// quitamos duplicados de la primera cadena
			if (!iter(argv[1], argv[1][i], i))
			{
				write(1, &argv[1][i], 1); // mostramos el caracter
			}
			i++;
		}
		while (argv[2][j])
		{
			// quitamos duplicados de la segunda cadena y duplicados entre la primera y segunda
			if (!iter(argv[1], argv[2][j], -1) && !iter(argv[2], argv[2][j], j))
			{
				write(1, &argv[2][j], 1); // mostramos el caracter
			}
			j++;
		}
	}
	// Siempre al final imprimimos un salto de línea
	write(1, "\n", 1);
	return (0);
}