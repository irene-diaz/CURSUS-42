#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		i;
	char	c;

	if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
		{
			c = argv[1][i];
			if ((c >= 'a' && c <= 'y') || (c >= 'A' && c <= 'Y'))
			{
				c += 1;
			}
			else if (c == 'z')
			{
				c = 'a';
			}
			else if (c == 'Z')
			{
				c = 'A';
			}
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
