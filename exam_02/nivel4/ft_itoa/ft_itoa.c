#include <stdlib.h>

/*count digits
mirar negativos
convertir en long
recorrer al	reves(parecido al punbr)
agregar negativo*/
int	count_digits(long n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	long	n;
	int		len;
	int		is_negative;
	char	*str;

	n = nbr;
	len = count_digits(n);
	is_negative = 0;
	if (n < 0)
	{
		n = -n;
		is_negative = 1;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
	{
		return (NULL);
	}
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (is_negative)
	{
		str[0] = '-';
	}
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	char *s;

	s = ft_itoa(19);
	printf("%s\n", s);
	free(s);

	s = ft_itoa(-2147483648);
	printf("%s\n", s);
	free(s);

	s = ft_itoa(0);
	printf("%s\n", s);
	free(s);

	return (0);
}*/