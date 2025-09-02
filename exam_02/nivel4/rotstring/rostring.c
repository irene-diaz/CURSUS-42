#include <unistd.h>

//comprueba si el caracter es una espacio o una tabulacion si lo es devuleve 1 sino lo es devuleve 0
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}
//imprimimos cada palabra
void	print_word(char *str, int start, int end)
{
	while (start < end)
		write(1, &str[start++], 1);
}

int	main(int argc, char **argv)
{
	int i = 0;
    int start;
    int end;
    int first_word_end = 0;
    int first_word_start = 0;
    int printed_word = 0;

    //si tiene mas de 1 argumento
	if (argc >= 2)
	{
		// Saltar espacios al principio
		while (is_space(argv[1][i]))
			i++;

        //GUARDAR LA PRIMERA PALABRA
		//Guardar donde empieza la primera palabra
		first_word_start = i;
        //recorremos la primera palabra y comprobamos que no sean espacios ni tabluaciones
		while (argv[1][i] && !is_space(argv[1][i]))
			i++;
        // Guardamos el final de la primera palabra
		first_word_end = i;

		//IMPRIMIR EL RESTO DE PALABRAS
		while (argv[1][i])
		{
            //saltamos espacio y tabulaciones, con esto nos aseguramos de estar al inicio de una nueva palabra
			while (is_space(argv[1][i]))
				i++;
            //guardamos la posicion de inicio de la nueva palabra
			start = i;
            //recorremos la palabra comprobando que no se traten de espacios ni tabs
			while (argv[1][i] && !is_space(argv[1][i]))
				i++;
            //guardamos la posicion de final de la nueva palabra
			end = i;

            //si existe la palabra, imprimela
			if (start < end)
			{
                //Sino es la primera palabra, imprime un espacio entre cada palabra
				if (printed_word)
					write(1, " ", 1);
                //imprimimos cada palabra
				print_word(argv[1], start, end);
                //Se activa para indicar que no estamos en la primera palabra
				printed_word= 1;
			}
		}

		
		// Añadir la primera palabra al final
		if (printed_word)
		{
			write(1, " ", 1);
			print_word(argv[1], first_word_start, first_word_end);
		}
		else
			print_word(argv[1], first_word_start, first_word_end);
	}
	write(1, "\n", 1);
	return (0);
}