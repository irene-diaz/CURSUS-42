void	sort_int_tab(int *tab, unsigned int size)
{
	int	temp;
	int	swapped;
	int	i;

	// si hay menos de dos numeros, ya estan ordenados
	if (size < 2)
		return ;
	do
	{
		swapped = 0;
		i = 0;
		// Recorre el array hasta el penúltimo elemento
		while (i < size - 1)
		{
			// Si el elemento actual es mayor que el siguiente, los intercambia
			if (tab[i] > tab[i + 1])
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	} while (swapped);
}

#include <stdio.h>

int	main(void)
{
	int				arr[] = {5, 2, 8, 1, 3};
	unsigned int	size;

	// ✅ forma correcta de saber el tamaño de un array
	size = sizeof(arr) / sizeof(arr[0]);
	sort_int_tab(arr, size);
	for (unsigned int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
