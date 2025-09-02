#include <unistd.h>

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}
void	ft_puthex(int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
	{
		ft_puthex(n / 16);
	}
	write(1, &hex[n % 16], 1);
}
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int n = ft_atoi(argv[1]);
		ft_puthex(n);
		// printf("%d", n);
	}
	write(1, "\n", 1);
}