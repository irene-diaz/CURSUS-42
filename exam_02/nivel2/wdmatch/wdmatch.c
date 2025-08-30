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
		int len = ft_strlen(argv[1]);
		int i = 0;
		int j = 0;
		int cont = 0;
		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
			{
				i++;
			}
			j++;
		}
		/*if (i == len)
		{
			write(1, argv[1], len);
		}*/
		int k = 0;
		while (i == len && argv[1][k])
		{
			write(1, &argv[1][k], 1); // imprime un carácter a la vez
			k++;
		}
	}
	write(1, "\n", 1);
}