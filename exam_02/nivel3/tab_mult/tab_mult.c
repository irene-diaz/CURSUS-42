#include <unistd.h>

//#include <stdio.h>

int	ft_atoi(char *str)
{
	int		i;
	int		res;
	char	c;

	i = 0;
	res = 0;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
		{
			res *= 10;
			res += str[i] - '0';
		}
		i++;
	}
	return (res);
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
int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int n = ft_atoi(argv[1]);
		int result = 0;
		int i = 1;
		while (i <= 9)
		{
			result = n * i;
			ft_putnbr(n);
			write(1, " x ", 3);
			ft_putnbr(i);
			write(1, " = ", 3);
			ft_putnbr(result);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		write(1, "\n", 1);
	}
}