#include <stdio.h>
#include <stdlib.h>

void	powerset(int *arr, int size, int target, int *subset, int subset_len,
		int index, int *result)
{
	int	sum;
	int	i;

	sum = 0;
	for (i = 0; i < subset_len; i++)
		sum += subset[i];
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
	for (i = index; i < size; i++)
	{
		subset[subset_len] = arr[i];
		powerset(arr, size, target, subset, subset_len + 1, i + 1, result);
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);

	int *arr;
	int target = atoi(argv[1]);
	int i;
	int n = argc - 2;
	int result = 0;

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

	powerset(arr, n, target, subset, 0, 0, &result);

	if (result == 0)
		printf("\n");

	free(arr);
	free(subset);

	return (0);
}