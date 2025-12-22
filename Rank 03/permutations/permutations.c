#include <stdlib.h>
#include <unistd.h>

// función para imprimir un string + '\n' usando write
void	putstr_ln(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

// función para intercambiar dos caracteres
void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// ordena la cadena en orden alfabético (simple bubble sort)
void	sort_string(char *s)
{
	char	tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[j] < s[i])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

// backtracking para generar permutaciones
/*int start= inicio de la cadena(indice)
int end=final de la cadena(indice)*/
void	permute(char *str, int start, int end)
{
	int	i;

	/* Caso base: Si start == end,
		significa que hemos fijado todos los caracteres hasta el final.*/
	if (start == end)
	{
		putstr_ln(str);
		return ;
	}
	i = start;
	// con este bucle hacemos todas las permutaciones posibles de la subcadena str[l..r]
	while (i <= end)
	{
		/*Intercambia el carácter en la posición start con el carácter en la posición i.
		Esto fija el carácter que estará en la posición start para esta permutación.*/
		swap(&str[start], &str[i]);
		// Llamada recursiva: permutamos la subcadena restante (desde start+1 hasta end).
		permute(str, start + 1, end);
		/*Después de explorar todas las permutaciones que comienzan con str[start] en esta posición,
		deshacemos el swap para restaurar la cadena original.
		Esto es fundamental para no alterar la cadena al probar otras combinaciones.*/
		swap(&str[start], &str[i]); // backtrack
		// Avanzamos para probar otro carácter en la posición l
		i++;
	}
}

int	main(int argc, char **argv)
{
	int len = 0;

	// control de agumentos
	if (argc != 2)
		return (1);
	// calculamos la longitud de la cadena dada por agurmento
	while (argv[1][len])
		len++;
	// ordenar primero para asegurar orden alfabético
	sort_string(argv[1]);
	// hacemos las permutaciones que permita el string
	permute(argv[1], 0, len - 1);
	return (0);
}