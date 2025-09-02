#include <unistd.h>

int	is_min(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	is_cap(char c)
{
	if (c >= 'A' && c <= 'Z')
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
	if (argc == 2)
	{
		int i = 0;
		while (argv[1][i])
		{
			char c = argv[1][i];
			if (is_min(argv[1][i]))
			{
				c = c - 32;
			}
			else if (is_cap(argv[1][i]))
			{
				c = c + 32;
			}
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
}