
int	get_values(char c)
{
	if (c >= '0' && c <= '9')
	{
		c = c - '0';
	}
	else if (c >= 'a' && c <= 'f')
	{
		c = c - 'a' + 10;
	}
	else if (c >= 'A' && c <= 'F')
	{
		c = c - 'A' + 10;
	}
	return (c);
}
int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	i;
	int	value;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		value = get_values(str[i]);
		if (value < 0 || value >= str_base)
		{
			break ;
		}
		result = result * str_base + value;
		i++;
	}
	return (result * sign);
}

/*#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_atoi_base("A", 16));   // 10
	printf("%d\n", ft_atoi_base("10", 2));   // 2
	printf("%d\n", ft_atoi_base("FF", 16));  // 255
	printf("%d\n", ft_atoi_base("-FF", 16)); // -255
	printf("%d\n", ft_atoi_base("21", 4));   // 9
	return (0);

	/*EJEMPLOS
		FF
		0*16+15=15
		15*16+15= 255

		10
		0*2+1= 1
		1*2+0=2;

		21
		0*4+2= 2
		2*4+1= 9
}*/