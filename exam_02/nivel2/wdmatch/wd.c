#include <unistd.h>

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
		// Recorremos cada carácter de argv[1] y de argv[2]
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