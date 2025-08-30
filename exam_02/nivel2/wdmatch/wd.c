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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
int	main(int argc, char *argv[])
{
	int i;

	// El programa solo funciona si se pasan EXACTAMENTE 2 argumentos:
	// ./a.out string1 string2
	if (argc == 3)
	{
		i = 0;
		int j = 0;
		int cont = 0;
		// Recorremos cada carácter de argv[1] (el primer string)
		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
			{
				cont++;
				i++;
			}
			j++;
		}
		if (cont == ft_strlen(argv[1]))
		{
			write(1, argv[1], ft_strlen(argv[1]));
		}
	}
	// Siempre al final imprimimos un salto de línea
	write(1, "\n", 1);
	return (0);
}