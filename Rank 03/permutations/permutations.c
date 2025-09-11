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
/*int l= inicio de la cadena(indice)
int r=final de la cadena(indice)*/
void	permute(char *str, int l, int r)
{
	int	i;

	/* Caso base: Si l == r,
		significa que hemos fijado todos los caracteres hasta el final.*/
	if (l == r)
	{
		putstr_ln(str);
		return ;
	}
	i = l;
	// con este bucle hacemos todas las permutaciones posibles de la subcadena str[l..r]
	while (i <= r)
	{
		/*Intercambia el carácter en la posición l con el carácter en la posición i.
		Esto fija el carácter que estará en la posición l para esta permutación.*/
		swap(&str[l], &str[i]);
		// Llamada recursiva: permutamos la subcadena restante (desde l+1 hasta r).
		permute(str, l + 1, r);
		/*Después de explorar todas las permutaciones que comienzan con str[l] en esta posición,
		deshacemos el swap para restaurar la cadena original.
		Esto es fundamental para no alterar la cadena al probar otras combinaciones.*/
		swap(&str[l], &str[i]); // backtrack
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