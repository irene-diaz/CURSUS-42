#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int i = 0;
		int cont = 0;
		int j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
			{
				cont++;
				i++;
			}
			j++;
		}

		if (cont == ft_strlen(argv[1]))
		{
			write(1, "1", 1);
		}
		else
		{
			write(1, "0", 1);
		}
	}
	write(1, "\n", 1);
}