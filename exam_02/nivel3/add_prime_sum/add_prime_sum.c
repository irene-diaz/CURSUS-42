#include <unistd.h>

int	atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	sign = 1;
	i = 0;
	res = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	write(1, &c, 1);
}
int	is_prime(int n)
{
	int	i;
	int	cont;

	i = 2;
	cont = 0;
	while (i <= n)
	{
		if (n % i == 0)
		{
			cont++;
		}
		i++;
	}
	if (cont == 1)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	main(int argc, char *argv[])
{
	int n;
	int sum;
	int i;

	if (argc != 2)
	{
		write(1, "0\n", 2);
		return (0);
	}
	n = atoi(argv[1]);
	if (n <= 0)
	{
		write(1, "0\n", 2);
		return (0);
	}
	sum = 0;
	i = 0;
	while (i <= n)
	{
		if (is_prime(i))
		{
			sum += i;
		}
		i++;
	}
	ft_putnbr(sum);
	write(1, "\n", 1);
}