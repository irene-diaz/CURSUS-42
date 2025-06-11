#include <unistd.h>

int	main(int argc, char **argv)
{
	int i;

    //nos aseguramos de que haya 3 argumentos y que el 2 y 3 argumento sea solo 1 letra
	if (argc != 4 || argv[2][1] != '\0' || argv[3][1] != '\0')
	{
		write(1, "\n", 1);
		return (0);
	}

	i = 0;

    //recorremos el string
	while (argv[1][i])
	{
        //Si el carácter actual de la cadena coincide con el que queremos reemplazar (argv[2][0]), escribimos el nuevo carácter (argv[3][0]).
		if (argv[1][i] == argv[2][0])
			write(1, &argv[3][0], 1);
        //Si no, escribimos el carcter original
		else
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}