unsigned int	hcf(unsigned int n1, unsigned int n2)
{
	while (n1 != n2)
	{
		if (n1 > n2)
		{
			n1 = n1 - n2;
		}
		else
		{
			n2 = n2 - n1;
		}
	}
	return (n1);
}

unsigned int	lcm(unsigned int a, unsigned int b)
{
	int	result;

	if (a == 0 || b == 0)
	{
		return (0);
	}
	result = a * b / (hcf(a, b));
	return (result);
}

/*#include <stdio.h>

int	main(void)
{
	printf("%u\n", lcm(12, 18)); // 36
	printf("%u\n", lcm(0, 5));   // 0
	printf("%u\n", lcm(7, 3));   // 21
}*/