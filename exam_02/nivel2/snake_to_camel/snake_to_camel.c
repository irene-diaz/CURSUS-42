#include <unistd.h>

int	is_underscore(char c)
{
	if (c == '_')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
char	capitalize(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		int i = 0;
		while (argv[1][i])
		{
			char c = argv[1][i];

			if (is_underscore(c))
			{
				c = capitalize(argv[1][i + 1]);
				i++;
			}
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
}