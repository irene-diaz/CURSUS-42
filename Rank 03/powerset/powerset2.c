#include <stdio.h>
#include <stdlib.h>

void	powerset(int *arr, int size, int target, int *subset, int subset_len,
		int index)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	for (i = 0; i < subset_len; i++)
	{
		sum += subset[i];
	}
	if (sum == target)
	{
		for (i = 0; i < subset_len; i++)
		{
			printf("%d", subset[i]);
			if (i != subset_len - 1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	for (i = index; i < size; i++)
	{
		subset[subset_len] = arr[i];
		powerset(arr, size, target, subset, subset_len + 1, i + 1);
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);

	int target = atoi(argv[1]);
	int n;
	int i;
	int *arr;

	n = argc - 2;
	arr = malloc(sizeof(int) * n);

	if (!arr)
		return (1);
	for (i = 0; i < n; i++)
	{
		arr[i] = atoi(argv[i + 2]);
	}
	int *subset;
	subset = malloc(sizeof(int) * n);

	if (!subset)
	{
		free(arr);
		return (1);
	}

	powerset(arr, n, target, subset, 0, 0);

	free(arr);
	free(subset);
}