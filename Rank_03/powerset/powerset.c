#include <stdio.h>
#include <stdlib.h>

// función recursiva que genera subconjuntos
/*arr → arreglo original de enteros.

size → número de elementos en arr.

target → suma objetivo.

subset → arreglo temporal que guarda el subconjunto actual.

subset_len → longitud actual del subconjunto.

index → índice desde donde se elige el siguiente elemento para evitar duplicados y mantener el orden.*/
void	powerset(int *arr, int size, int target, int *subset, int subset_len,
		int index, int *result)
{
	int	i;
	int	sum;

	sum = 0;
	// calcular suma del subset actual
	for (i = 0; i < subset_len; i++)
		sum += subset[i];
	// si la suma coincide, imprimimos el subset
	if (sum == target)
	{
		*result = 1;
		for (i = 0; i < subset_len; i++)
		{
			printf("%d", subset[i]);
			if (i != subset_len - 1)
				printf(" ");
		}
		printf("\n");
	}
	// explorar nuevas opciones
	for (i = index; i < size; i++)
	{
		subset[subset_len] = arr[i];
		powerset(arr, size, target, subset, subset_len + 1, i + 1, result);
	}
}

int	main(int argc, char **argv)
{
	int target;
	int *arr;
	int i;
	int n;
	int result = 0;

	// control de argumentos
	if (argc < 2)
		return (1);

	// convertimos la cadena de suma objetivo en un nº
	target = atoi(argv[1]);
	// cojemos el numero de numeros de la serie que le pasamos por agumentos(le quitamos el nombre del programa y la sum aobjetivo)
	n = argc - 2;
	// reservamos memoria para ese array
	arr = malloc(sizeof(int) * n);
	if (!arr)
		return (1); // malloc error

	for (i = 0; i < n; i++)
		arr[i] = atoi(argv[i + 2]);

	int *subset = malloc(sizeof(int) * n);
	if (!subset)
	{
		free(arr);
		return (1);
	}

	powerset(arr, n, target, subset, 0, 0, &result);

	if (result == 0)
		printf("\n");

	free(arr);
	free(subset);
	return (0);
}