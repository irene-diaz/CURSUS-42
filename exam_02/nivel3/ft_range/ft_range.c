#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	len;
	int	*array;
	int	i;

	len = 0;
	if (start <= end)
	{
		len = (end - start) + 1;
	}
	else
	{
		len = (start - end) + 1;
	}
	array = malloc(len * sizeof(int));
	if (!array)
	{
		return (NULL);
	}
	i = 0;
	if (start <= end)
	{
		while (start <= end)
		{
			array[i++] = start++;
		}
	}
	else
	{
		while (start >= end)
		{
			array[i++] = start--;
		}
	}
	return (array);
}
/*#include <stdio.h>

int	main(void)
{
	int	*n;
	int	i;

	n = ft_range(1, 3); // debe crear [1, 2, 3]
	for (i = 0; i < 3; i++)
		printf("%d ", n[i]);
	printf("\n");
	n = ft_range(3, 1); // debe crear [3, 2, 1]
	for (i = 0; i < 3; i++)
		printf("%d ", n[i]);
	printf("\n");
	return (0);
}*/
