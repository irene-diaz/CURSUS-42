#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++, i++;
	}
	return (i);
}
int	main(int argc, char *argv[])
{
	int	i;

	if (argc == 2)
	{
		i = ft_strlen(argv[1]);
		while (i--)
		{
			write(1, &argv[1][i], 1);
		}
	}
	write(1, "\n", 1);
}