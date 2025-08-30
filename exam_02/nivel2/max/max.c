int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int				max;

	// comprobamos primero si la tabla esta vacia o si el puntero no apunta a nada
	if (!tab || len == 0)
	{
		return (0);
	}
	// Tomamos como valor máximo inicial el primer elemento del array(base para comprobar el resto de numeros)
	max = tab[0];
	// Empezamos en i = 1 (el segundo elemento),porque el tab[0] ya lo usamos.
	i = 1;
	while (i < len)
	{
		// Si encontramos un número mayor que el max actual,lo actualizamos,sino dejamos el max como esta
		if (tab[i] > max)
		{
			max = tab[i];
		}
		i++;
	}
	return (max);
}

/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int *array;
	int len = 6;

	int *array2 = NULL;

	array = malloc(len * sizeof(int));
	array[0] = 3;
	array[1] = 6;
	array[2] = 1;
	array[3] = 2;
	array[4] = 8;
	array[5] = 5;

	for (int i = 0; i < len; i++)
	{
		printf("%d\n", array[i]);
	}

	printf("El mayor numero es el %d\n", max(array, len));
	printf("El mayor numero es el %d\n", max(array2, len));

	free(array);
	return (0);
}*/